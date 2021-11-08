/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MU_AUTOBOT_AUTOBOTSCRIPTSMODEL_H
#define MU_AUTOBOT_AUTOBOTSCRIPTSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QMap>

#include "modularity/ioc.h"
#include "../iautobotscriptsrepository.h"
#include "../iautobot.h"
#include "async/asyncable.h"

namespace mu::autobot {
class AutobotScriptsModel : public QAbstractListModel, public async::Asyncable
{
    Q_OBJECT
    Q_PROPERTY(bool isRunAllTCMode READ isRunAllTCMode WRITE setIsRunAllTCMode NOTIFY isRunAllTCModeChanged)

    INJECT(autobot, IAutobotScriptsRepository, scriptsRepository)
    INJECT(autobot, IAutobot, autobot)

public:
    explicit AutobotScriptsModel(QObject* parent = nullptr);
    ~AutobotScriptsModel();

    QVariant data(const QModelIndex& index, int role) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool isRunAllTCMode() const;

    Q_INVOKABLE void load();
    Q_INVOKABLE void runScript(int scriptIndex);

    Q_INVOKABLE void runAllTC();
    Q_INVOKABLE bool tryRunNextTC();
    Q_INVOKABLE void stopRunAllTC();

public slots:
    void setIsRunAllTCMode(bool arg);

signals:
    void isRunAllTCModeChanged();
    void requireStartTC(const QString& path);

private:

    enum Roles {
        rTitle = Qt::UserRole + 1,
        rDescription,
        rType,
        rPath,
        rIndex,
        rStatus
    };

    void setStatus(const io::path& path, IAutobot::Status st);

    Scripts m_scripts;
    int m_currentTCIndex = -1;
    bool m_isRunAllTCMode = false;
    QMap<io::path, IAutobot::Status> m_statuses;
};
}

#endif // MU_AUTOBOT_AUTOBOTSCRIPTSMODEL_H
