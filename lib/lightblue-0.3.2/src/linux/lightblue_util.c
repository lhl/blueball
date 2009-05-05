/*
 * Copyright (c) 2006 Bea Lam. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Extension module to access BlueZ operations not provided in PyBluez. 
 */

#include "Python.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

/*
 * Returns name of local device
 */
static PyObject* lb_hci_read_local_name(PyObject *self, PyObject *args)
{
    int err = 0;
    int timeout = 0;
    int fd = 0;
    char name[249];

    if (!PyArg_ParseTuple(args, "ii", &fd, &timeout))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    err = hci_read_local_name(fd, sizeof(name)-1, name, timeout);
    Py_END_ALLOW_THREADS

    if (err != 0)
        return PyErr_SetFromErrno(PyExc_IOError);

    return PyString_FromString(name);    
}

/*
 * Returns address of local device
 */
static PyObject* lb_hci_read_bd_addr(PyObject *self, PyObject *args)
{
    int err = 0;
    int timeout = 0;
    int fd = 0;
    bdaddr_t ba;
    char addrstr[19] = {0};
    
    if (!PyArg_ParseTuple(args, "ii", &fd, &timeout))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    err = hci_read_bd_addr(fd, &ba, timeout);
    Py_END_ALLOW_THREADS

    if (err != 0)
        return PyErr_SetFromErrno(PyExc_IOError);

    ba2str(&ba, addrstr);
    return PyString_FromString(addrstr);
}

/*
 * Returns class of device of local device as a
 * (service, major, minor) tuple 
 */
static PyObject* lb_hci_read_class_of_dev(PyObject *self, PyObject *args)
{
    int err = 0;
    int timeout = 0;
    int fd = 0;
    uint8_t cod[3];
    
    if (!PyArg_ParseTuple(args, "ii", &fd, &timeout))
        return NULL;
        
    Py_BEGIN_ALLOW_THREADS
    err = hci_read_class_of_dev(fd, cod, timeout);
    Py_END_ALLOW_THREADS

    if (err != 0)
        return PyErr_SetFromErrno(PyExc_IOError);
    
    return Py_BuildValue("(B,B,B)", cod[2] << 3, cod[1] & 0x1f, cod[0] >> 2);
}

/* list of all functions in this module */
static PyMethodDef utilmethods[] = {
    {"hci_read_local_name", lb_hci_read_local_name, METH_VARARGS },
    {"hci_read_bd_addr", lb_hci_read_bd_addr, METH_VARARGS},
    {"hci_read_class_of_dev", lb_hci_read_class_of_dev, METH_VARARGS},
    { NULL, NULL }  /* sentinel */
};

/* module initialization functions */
void init_lightblueutil(void) {
    Py_InitModule("_lightblueutil", utilmethods);
}
