#include "plugin.h"
#include <QDir>

Plugin::Plugin()
{
	m_outputImagePath = Settings::instance()->
		stringOrDefault("session", "sequenceDir");
	m_sequence = Settings::instance()->intOrDefault("session", "sequenceNum", 0);
}

void Plugin::setPathAndSequenceStart(QFileInfo path, int start)
{
	m_outputImagePath = path;
	m_sequence = start;
	Settings::instance()->setString("session", "sequenceDir", path.absoluteFilePath());
	Settings::instance()->setInt("session", "sequenceNum", m_sequence);
}

QFileInfo Plugin::takeNextImageOutput()
{
	QFileInfo ret = nextImageOutput();
	++m_sequence;
	Settings::instance()->setInt("session", "sequenceNum", m_sequence);
	return ret;
}

QFileInfo Plugin::nextImageOutput()
{
	QFileInfo ret(m_outputImagePath.dir(),
		QString("%1/image%2.%3").arg(m_outputImagePath.fileName())
			.arg(m_sequence, 4, 10, QLatin1Char('0')).arg(fileExt()));
	return ret;
}
