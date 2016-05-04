#ifndef VIDEOSEQUENCE_H
#define VIDEOSEQUENCE_H
#include <QTime>
#include <QString>
#include <QUuid>
#include <QMetaType>

/*!
 * \brief The VideoSequence class is used as a wrapper around the video footage of the drone.
 * \ingroup Models
 */
class VideoSequence
{
public:
    /*!
     * \brief VideoSequence default constructor
     * Creates a default VideoSequence.
     */
    VideoSequence();
    /*!
     * \brief VideoSequence copy constructor
     */
    VideoSequence(const VideoSequence &d);
    /*!
     * \brief VideoSequence destructor
     */
    ~VideoSequence();
    /*!
     * \brief VideoSequence constructor
     * \param videoId is the unique id of the VideoSequence.
     */
    VideoSequence(QUuid videoId);
    /*!
     * \brief VideoSequence constructor
     * \param videoId is the unique id of the VideoSequence.
     * \param path is the path of the VideoSequence.
     */
    VideoSequence(QString path, QUuid videoId);
    /*!
     * \brief VideoSequence constructor
     * \param start is the start time of the VideoSequence.
     * \param end is the end time of the VideoSequence.
     * \param frameCount is the number of frames of the VideoSequence.
     * \param path is the path of the VideoSequence.
     */
    VideoSequence(QUuid videoId, QTime start, QTime end, int frameCount, QString path);

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
