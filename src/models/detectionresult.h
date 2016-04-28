#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H
#include <QGeoCoordinate>
#include "models/videosequence.h"

/*!
 * \brief The DetectionResult class
 * \ingroup Models
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
     * \param location, the geocoordinate of the detection.
     * \param score, the score of the detection (measure of accuracy).
     */
    DetectionResult(QGeoCoordinate location, double score);
    //getters
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
    QGeoCoordinate location;
    double score;
};

Q_DECLARE_METATYPE(DetectionResult)

#endif // DETECTIONRESULT_H
