#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QFileInfo>
#include "common.h"

/**
	Interface for disk image capture plugins.
*/
class Plugin : public QObject
{
	Q_OBJECT

public:
	Plugin();

	/**
	  @param path partial file path, e.g. /path/to/archive/seq1/image
			to which the sequence number and file extension will be appended
	*/
	void setPathAndSequenceStart(QFileInfo path, int start = 0);
	QFileInfo takeNextImageOutput();
	QFileInfo nextImageOutput();
	int nextSequenceNumber() { return m_sequence; }
	void setNextSequenceNumber(int val) { m_sequence = val; }
	virtual void start(QFileInfo device) = 0;
	virtual QString name() = 0;
	virtual QString fileExt() = 0;

signals:
	void totalRecords(int zero, int num);
	void recordsCopied(int num);
	void done(bool success);

protected:
	int m_sequence;
	QFileInfo m_outputImagePath;
};

#endif // PLUGIN_H
