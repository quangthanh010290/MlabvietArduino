//
//  Copyright (c) 2014 Texas Instruments. All rights reserved.
//

package com.pandaos.smartconfig.utils;

import com.googlecode.androidannotations.annotations.sharedpreferences.DefaultBoolean;
import com.googlecode.androidannotations.annotations.sharedpreferences.DefaultInt;
import com.googlecode.androidannotations.annotations.sharedpreferences.DefaultString;
import com.googlecode.androidannotations.annotations.sharedpreferences.SharedPref;

@SharedPref
public interface SharedPreferencesInterface {

	@DefaultBoolean(true)
	boolean showDeviceName();
	
	@DefaultBoolean(false)
	boolean openInDevicesList();
	
	@DefaultBoolean(false)
	boolean showSmartConfigPass();
	
	@DefaultBoolean(false)
	boolean skipScanDisplay();
	
	@DefaultInt(0)
	int startTab();
	
	@DefaultBoolean(false)
	boolean isScanning();
	
	@DefaultBoolean(false)
	boolean isSmartConfigActive();
	
	@DefaultString("[]")
	String devicesArray();
	
	@DefaultString("[]")
	String recentDevicesArray();
	
}
