#pragma once

#include <observation_tree/CObservationTreeGui.h>
#include <calib_solvers/CCalibFromLines.h>
#include <interfaces/CLinesObserver.h>

#include <opencv2/core/core.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

/**
 * Provides a GUI wrapper around the core calibration from lines classes.
 */

class CCalibFromLinesGui : public CCalibFromLines
{
public:

	/**
	 * Constructor
	 * \param model the rawlog model.
	 * \param sync_obs_indices sync_obs_indices indices of the grouped (synchronized) observations in the original model, per sensor.
	 */
	CCalibFromLinesGui(CObservationTree *model, TCalibFromLinesParams *params);

	~CCalibFromLinesGui();

	/** Runs line segmentation on all the image observations in the model. */
	void extractLines();

	/** Runs line matching. */
	void matchLines();

	/** Adds observer to list of text observers. */
	void addTextObserver(CTextObserver *observer);

	/** Adds observer to list of line observers. */
	void addLinesObserver(CLinesObserver *observer);

	/** Adds observer to list of matched lines observers. */
	//void addCorrespLinesObserver(CCorrespLinesObserver *observer);

	/** Notifies text observers with a message. */
	void publishText(const std::string &msg);

	/** Notifies observers with the extracted lines.
	 * \param sensor_id id of the sensor the lines were observed from.
	 * \param sync_obs_id id of the observation in the synchronized rawlog.
	 */
	void publishLines(const int &sensor_id, const int &sync_obs_id);

	/** Returns the status of the calibration progress. */
	CalibrationFromLinesStatus calibStatus();


private:

	/** The parameters for the calibration. */
	TCalibFromLinesParams *m_params;

	/** List of text observers to be notified about progress status. */
	std::vector<CTextObserver*> m_text_observers;

	/** List of observers to be notified about extracted lines. */
	std::vector<CLinesObserver*> m_lines_observers;
};
