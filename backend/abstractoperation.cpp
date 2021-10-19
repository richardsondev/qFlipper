#include "abstractoperation.h"

#include <QTimer>

#include "macros.h"

AbstractOperation::AbstractOperation(QObject *parent):
    QObject(parent),
    m_timeout(new QTimer(this)),
    m_operationState(BasicOperationState::Ready)
{
    connect(m_timeout, &QTimer::timeout, this, &AbstractOperation::onOperationTimeout);
    m_timeout->setSingleShot(true);
}

void AbstractOperation::finish()
{
    stopTimeout();
    setOperationState(AbstractOperation::Finished);

    emit finished();
}

int AbstractOperation::operationState() const
{
    return m_operationState;
}

void AbstractOperation::onOperationTimeout()
{
    finishWithError(QStringLiteral("Operation timeout (generic)"));
}

void AbstractOperation::setOperationState(int state)
{
    m_operationState = state;
}

void AbstractOperation::finishWithError(const QString &errorMsg)
{
    setError(errorMsg);
    finish();
}

void AbstractOperation::startTimeout(int msec)
{
    m_timeout->start(msec);
}

void AbstractOperation::stopTimeout()
{
    m_timeout->stop();
}