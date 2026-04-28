#pragma once
#include <qobject.h>
#include <qmutex.h>
#include <qimage.h>
#include <qthread.h>
#include <QCoreApplication>
#include <SettingDialog.h>

struct AnalyzerAlgorithm {
    enum class AlgorithmType{
        Sharpness,
        FeatureMatching,
        Detection
    };
    AlgorithmType algorithmType;
};
using AlgorithmType = AnalyzerAlgorithm::AlgorithmType;
static const QList<QString> supportedAlgorithms = {
    "Sharpness",
    "Feature Matching",
    "Detection"
};

class AnalyzerBase : public QObject
{
    Q_OBJECT

public:
    explicit AnalyzerBase(QObject* parent = nullptr);
    virtual ~AnalyzerBase() = default;

public slots:
    void analyze(const QImage& image);
    void setParams(const AnalyzerParameters& params);

private slots:
    void processLatest();

signals:
    void resultReady(double value);
    void resultTimeCounted(double ms);

protected:
    virtual double imageProcess(const QImage& image) = 0;
    AnalyzerParameters* getParams() const { return m_params; }

private:
    QMutex              m_mutex;
    bool                m_hasNew{ false };
    bool                m_processing{ false };
    QImage              m_latestImage;
    AnalyzerParameters* m_params{ nullptr };
    double              m_timeCount{ 0.0 };
};

class AnalyzerFactory
{
public:
    static AnalyzerBase* createAnalyzer(AlgorithmType type, QObject* parent = nullptr);
    static QString       getAnalyzerName(AlgorithmType type);
};

class AnalyzerThreadManager : public QObject
{
    Q_OBJECT

public:
    explicit AnalyzerThreadManager(QObject* parent = nullptr)
    :   QObject(parent)
    , m_thread(new QThread(this))
    , m_currentAnalyzer(nullptr)
    {
        m_thread->start();
    }
    ~AnalyzerThreadManager() override
    {
        // 安全退出线程
        if (m_thread) {
            m_thread->quit();
            m_thread->wait();
        }
    }

    template<typename T> void createAnalyzer();    // 创建新分析器 → 自动移入线程
    void analyzeImage(const QImage& image);        // 发送图片分析
    void setParameters(const AnalyzerParameters& params);  // 设置参数

signals:
    void resultReady(double value);
    void resultTimeCounted(double ms);

private:
    void safeDestroyCurrentAnalyzer()
    {
        if (!m_currentAnalyzer) 
            return;
        
        m_currentAnalyzer->disconnect();       // 1. 断开所有信号
        m_currentAnalyzer->deleteLater();      // 2. 在线程内部销毁（绝对安全）
        QCoreApplication::processEvents();     // 3. 等待销毁完成
        m_currentAnalyzer = nullptr;
    }

private:
    QThread*        m_thread;           // 唯一工作线程
    AnalyzerBase*   m_currentAnalyzer;  // 当前分析器
};

template<typename T>
inline void AnalyzerThreadManager::createAnalyzer()
{
    
    safeDestroyCurrentAnalyzer();              // 1. 安全销毁旧分析器
    T* analyzer = new T();                     // 2. 创建新分析器（无父对象，才能 moveToThread）
    m_currentAnalyzer = analyzer;
    analyzer->moveToThread(m_thread);          // 3. 移动到工作线程（关键）
    // 4. 连接结果信号
    connect(analyzer, &AnalyzerBase::resultReady,       this, &AnalyzerThreadManager::resultReady);
    connect(analyzer, &AnalyzerBase::resultTimeCounted, this, &AnalyzerThreadManager::resultTimeCounted);
}
