#ifndef EXCEPTION_H
#define EXCEPTION_H

/**
 * @file   customexception.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  Custom Exception class declaration.
 */

#include <QException>

/**
 * @brief The CustomException class implements a custom
 * Exception used to handle runtime errors inside the application.
 */
class CustomException : public QException
{
public:

    /**
     * @brief Class constructor.
     * @param message The exception message.
     */
    explicit CustomException(const QString& message) : message_(message) {
        // Nothing to do here
    }

    /**
     * @brief Class destructor.
     */
    virtual ~CustomException() {
        // Nothing to do here
    }

    /**
     * @return the exception message.
     */
    inline QString getMessage() const {
        return message_;
    }

private:
    QString message_;   //!< The exception message.
};

#endif // EXCEPTION_H
