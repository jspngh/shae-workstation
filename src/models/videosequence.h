#ifndef VIDEOSEQUENCE_H
#define VIDEOSEQUENCE_H
#include <QTime>
#include <QString>
#include <QUuid>
#include <QMetaType>

/*!
 * \brief The VideoSequence class
 * \ingroup Models
 */
class VideoSequence
{
public:
    //constructors
    VideoSequence();
    VideoSequence(const VideoSequence &d);
    ~VideoSequence();

    VideoSequence(QUuid videoId);
    VideoSequence(QString path, QUuid videoId);
    VideoSequence(QUuid videoId, QTime start, QTime end, int frameCount, QString path);

    //getters
    QUuid getVideoID();
    QTime getStart();
    QTime getEnd();
    int getFrameCount();

    QString getPath() const;
    void setPath(const QString &value);

private:
    QTime start;
    QTime end;
    int frameCount;
    QString path;
    QUuid videoId;
};

Q_DECLARE_METATYPE(VideoSequence)
#endif // VIDEOSEQUENCE_H
