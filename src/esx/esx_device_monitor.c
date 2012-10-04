
/*
 * esx_device_monitor.c: device monitor functions for managing VMware ESX
 *                       host devices
 *
 * Copyright (C) 2010-2011 Red Hat, Inc.
 * Copyright (C) 2010 Matthias Bolte <matthias.bolte@googlemail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

#include <config.h>

#include "internal.h"
#include "util.h"
#include "memory.h"
#include "logging.h"
#include "uuid.h"
#include "esx_private.h"
#include "esx_device_monitor.h"
#include "esx_vi.h"
#include "esx_vi_methods.h"
#include "esx_util.h"

#define VIR_FROM_THIS VIR_FROM_ESX



static virDrvOpenStatus
esxDeviceOpen(virConnectPtr conn,
              virConnectAuthPtr auth ATTRIBUTE_UNUSED,
              unsigned int flags)
{
    virCheckFlags(VIR_CONNECT_RO, VIR_DRV_OPEN_ERROR);

    if (conn->driver->no != VIR_DRV_ESX) {
        return VIR_DRV_OPEN_DECLINED;
    }

    conn->devMonPrivateData = conn->privateData;

    return VIR_DRV_OPEN_SUCCESS;
}



static int
esxDeviceClose(virConnectPtr conn)
{
    conn->devMonPrivateData = NULL;

    return 0;
}



static virDeviceMonitor esxDeviceMonitor = {
    .name = "ESX",
    .open = esxDeviceOpen, /* 0.7.6 */
    .close = esxDeviceClose, /* 0.7.6 */
};



int
esxDeviceRegister(void)
{
    return virRegisterDeviceMonitor(&esxDeviceMonitor);
}