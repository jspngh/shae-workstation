#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include "models/videosequence.h"

/*!
 * \brief The DetectionResult class
 * \ingroup Models
 This class contains the detections score (probability of human presence) and its location.
 */
class DetectionResult
{
public:
    /*!
     * \brief DetectionResult default constructor
     * Creates a default detection result.
     */
    DetectionResult();
    /*!
     * \brief DetectionResult copy constructor
     */
    DetectionResult(const DetectionResult &d);
    /*!
     * \brief DetectionResult destructor
     */
    ~DetectionResult();
    /*!
     * \brief default DetectionResult constructor
     * \param location is the geocoordinate of the detection.
     * \param score is the score of the detection (measure of accuracy).
     */
    DetectionResult(QGeoCoordinate location, double score);
    /*!
     * \brief getScore()
     * \return the score of the DetectionResult
     */
    double getScore();
    /*!
     * \brief getLocation()
     * \return the location of the DetectionResult
     */
    QGeoCoordinate getLocation();

private:
    QGeoCoordinate location; //!< the location of the score
    double score; //! the score is a double between 0 and 100
};

Q_DECLARE_METATYPE(DetectionResult)

#endif // DETECTIONRESULT_H
