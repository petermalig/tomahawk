/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MPRISPLUGIN_H
#define MPRISPLUGIN_H

#include "infosystem/infosystem.h"

#include <QObject>
#include <QVariant>
#include <QtDBus/QtDBus>

namespace Tomahawk {

namespace InfoSystem {

class MprisPlugin : public InfoPlugin
{
    Q_OBJECT

public:
    MprisPlugin();
    virtual ~MprisPlugin();

    // MPRIS DBus Methods

    // org.mpris.MediaPlayer2
    
    Q_PROPERTY(bool CanQuit READ canQuit)
    bool canQuit() const;

    Q_PROPERTY(bool CanRaise READ canRaise)
    bool canRaise() const;

    Q_PROPERTY(QString DesktopEntry READ desktopEntry)
    QString desktopEntry() const;

    Q_PROPERTY(bool HasTrackList READ hasTrackList)
    bool hasTrackList() const;

    Q_PROPERTY(QString Identity READ identity)
    QString identity() const;

    Q_PROPERTY(QStringList SupportedMimeTypes READ supportedMimeTypes)
    QStringList supportedMimeTypes() const;

    Q_PROPERTY(QStringList SupportedUriSchemes READ supportedUriSchemes)
    QStringList supportedUriSchemes() const;

    // org.mpris.MediaPlayer2.Player

    Q_PROPERTY(bool CanControl READ canControl)
    bool canControl() const;

    Q_PROPERTY(bool CanGoNext READ canGoNext)
    bool canGoNext() const;

    Q_PROPERTY(bool CanGoPrevious READ canGoPrevious)
    bool canGoPrevious() const;

    Q_PROPERTY(bool CanPause READ canPause)
    bool canPause() const;

    Q_PROPERTY(bool CanPlay READ canPlay)
    bool canPlay() const;

    Q_PROPERTY(bool CanSeek READ canSeek)
    bool canSeek() const;

    Q_PROPERTY(QString LoopStatus READ loopStatus WRITE setLoopStatus)
    QString loopStatus() const;
    void setLoopStatus(const QString &value);

    Q_PROPERTY(double MaximumRate READ maximumRate)
    double maximumRate() const;

    Q_PROPERTY(QVariantMap Metadata READ metadata)
    QVariantMap metadata() const;

    Q_PROPERTY(double MinimumRate READ minimumRate)
    double minimumRate() const;

    Q_PROPERTY(QString PlaybackStatus READ playbackStatus)
    QString playbackStatus() const;

    Q_PROPERTY(qlonglong Position READ position)
    qlonglong position() const;

    Q_PROPERTY(double Rate READ rate WRITE setRate)
    double rate() const;
    void setRate(double value);

    Q_PROPERTY(bool Shuffle READ shuffle WRITE setShuffle)
    bool shuffle() const;
    void setShuffle(bool value);

    Q_PROPERTY(double Volume READ volume WRITE setVolume)
    double volume() const;
    void setVolume(double value);

public slots:
    void namChangedSlot( QNetworkAccessManager* /*nam*/ ) {} // unused

    virtual void notInCacheSlot( uint requestId, const Tomahawk::InfoSystem::InfoCriteriaHash criteria, Tomahawk::InfoSystem::InfoRequestData requestData )
    {
        Q_UNUSED( requestId );
        Q_UNUSED( criteria );
        Q_UNUSED( requestData );
    }

    // org.mpris.MediaPlayer2
    void Raise();
    void Quit();

    // org.mpris.MediaPlayer2.Player
    void Next();
    void OpenUri(const QString &Uri);
    void Pause();
    void Play();
    void PlayPause();
    void Previous();
    void Seek(qlonglong Offset);
    void SetPosition(const QDBusObjectPath &TrackId, qlonglong Position);
    void Stop();


protected slots:
    void getInfo( uint requestId, Tomahawk::InfoSystem::InfoRequestData requestData );
    void pushInfo( QString caller, Tomahawk::InfoSystem::InfoType type, QVariant input );

private:
    // Get Info
    
    // Push Info
    void audioStarted( const QVariant &input );
    void audioFinished( const QVariant &input );
    void audioStopped();
    void audioPaused();
    void audioResumed( const QVariant &input );

};

};


}

#endif // MPRISPLUGIN_H
