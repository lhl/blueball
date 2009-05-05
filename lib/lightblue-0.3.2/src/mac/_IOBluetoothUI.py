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
Provides a python interface to the Mac OSX IOBluetoothUI Framework classes, 
through PyObjC.

For example:
    >>> from lightblue import _IOBluetoothUI
    >>> selector = _IOBluetoothUI.IOBluetoothDeviceSelectorController.deviceSelector()
    >>> selector.runModal()    # ask user to select a device
    -1000
    >>> for device in selector.getResults():
    ...     print device.getName()    # show name of selected device
    ... 
    Nokia 6600
    >>> 
    
See http://developer.apple.com/documentation/DeviceDrivers/Reference/IOBluetoothUI/index.html 
for Apple's IOBluetoothUI documentation.
    
See http://pyobjc.sourceforge.net for details on how to access Objective-C 
classes through PyObjC.
"""

import objc

try:
    # mac os 10.5 loads frameworks using bridgesupport metadata
    __bundle__ = objc.initFrameworkWrapper("IOBluetoothUI",
            frameworkIdentifier="com.apple.IOBluetoothUI",
            frameworkPath=objc.pathForFramework(
                "/System/Library/Frameworks/IOBluetoothUI.framework"),
            globals=globals())
            
except AttributeError:
    # earlier versions use loadBundle() and setSignatureForSelector()            
    
    objc.loadBundle("IOBluetoothUI", globals(), 
       bundle_path=objc.pathForFramework(u'/System/Library/Frameworks/IOBluetoothUI.framework'))

del objc
    