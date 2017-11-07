//
//  Copyright (c) 2014 Texas Instruments. All rights reserved.
//

package com.pandaos.smartconfig;

import android.support.v4.app.Fragment;
import android.widget.TextView;

import com.googlecode.androidannotations.annotations.Click;
import com.googlecode.androidannotations.annotations.EFragment;
import com.googlecode.androidannotations.annotations.ViewById;

@EFragment(R.layout.ap_mode_page6)
public class APModePage6 extends Fragment {

	@ViewById
	TextView ap_mode_page6_done;
	
	@Click
	void ap_mode_page6_done() {
		getActivity().finish();
	}
	
}