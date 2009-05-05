# Copyright (c) 2006 Bea Lam. All rights reserved.
# 
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

"""
Provides a python interface to the Mac OSX IOBluetooth Framework classes, 
through PyObjC.

For example:
    >>> from lightblue import _IOBluetooth
    >>> for d in _IOBluetooth.IOBluetoothDevice.recentDevices_(0):
    ...     print d.getName()
    ... 
    Munkey
    Adam
    My Nokia 6600
    >>> 
    
See http://developer.apple.com/documentation/DeviceDrivers/Reference/IOBluetooth/index.html 
for Apple's IOBluetooth documentation.    
    
See http://pyobjc.sourceforge.net for details on how to access Objective-C 
classes through PyObjC.
"""

import objc

try:
    # mac os 10.5 loads frameworks using bridgesupport metadata
    __bundle__ = objc.initFrameworkWrapper("IOBluetooth",
            frameworkIdentifier="com.apple.IOBluetooth",
            frameworkPath=objc.pathForFramework(
                "/System/Library/Frameworks/IOBluetooth.framework"),
            globals=globals())

except AttributeError:
    # earlier versions use loadBundle() and setSignatureForSelector()
    
    objc.loadBundle("IOBluetooth", globals(), 
       bundle_path=objc.pathForFramework(u'/System/Library/Frameworks/IOBluetooth.framework'))

    # Sets selector signatures in order to receive arguments correctly from
    # PyObjC methods. These MUST be set, otherwise the method calls won't work
    # at all, mostly because you can't pass by pointers in Python.

    # set to return int, and take an unsigned char output arg
    # i.e. in python: return (int, unsigned char) and accept no args
    objc.setSignatureForSelector("IOBluetoothSDPServiceRecord",     
            "getRFCOMMChannelID:", "i12@0:o^C") 
            
    # set to return int, and take an unsigned int output arg
    # i.e. in python: return (int, unsigned int) and accept no args    
    objc.setSignatureForSelector("IOBluetoothSDPServiceRecord",     
            "getL2CAPPSM:", "i12@0:o^S")
    
    # set to return int, and take (output object, unsigned char, object) args
    # i.e. in python: return (int, object) and accept (unsigned char, object)
    objc.setSignatureForSelector("IOBluetoothDevice", 
            "openRFCOMMChannelSync:withChannelID:delegate:", "i16@0:o^@C@") 

    # set to return int, and take (output object, unsigned int, object) args            
    # i.e. in python: return (int, object) and accept (unsigned int, object)    
    objc.setSignatureForSelector("IOBluetoothDevice", 
            "openL2CAPChannelSync:withPSM:delegate:", "i20@0:o^@I@")

    # set to return int, take a const 6-char array arg
    # i.e. in python: return object and accept 6-char list
    # this seems to work even though the selector doesn't take a char aray,
    # it takes a struct 'BluetoothDeviceAddress' which contains a char array.
    objc.setSignatureForSelector("IOBluetoothDevice", 
            "withAddress:", '@12@0:r^[6C]') 
   
del objc
