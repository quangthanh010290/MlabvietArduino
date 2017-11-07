//
//  Copyright (c) 2014 Texas Instruments. All rights reserved.
//

package com.pandaos.smartconfig;

import android.app.Activity;
import android.content.Intent;

import com.googlecode.androidannotations.annotations.AfterViews;
import com.googlecode.androidannotations.annotations.Background;
import com.googlecode.androidannotations.annotations.EActivity;
import com.pandaos.smartconfig.utils.SmartConfigConstants;

@EActivity(R.layout.activity_splash_screen)
public class SplashScreen extends Activity {
	
	@AfterViews
	void afterViews() {
		splash();
	}
	
	@Background
	void splash() {
		try {
			Thread.sleep(SmartConfigConstants.SPLASH_SCREEN_TIME);
		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {
			Intent intent = new Intent(this, MainActivity_.class);
			startActivity(intent);
			// close this activity
			finish();
		}
	}
	
	public void onBackPressed() {
		// ignore the back button
	}
}
