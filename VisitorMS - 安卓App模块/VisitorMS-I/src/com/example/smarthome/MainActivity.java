/**********************************************************************************************
 *    :|x].              ?ObU:        +jfl           ?Zdr'                   '"I>>iI"'        
 *    n$$${             x@$$k;       n$$$Mi         [B$$$c               "-xZ*%$$$$$%*pX+     
 *    >8$$k`           j$$$C^       ]$$$$$Q.       `k$$$$8l            ~Y#$$%kQznnuY0qhk|     
 *     j$$$n          {@$$0'       .q$$$$$B<       ($$$$$$/          'uB$$p{:                 
 *     'm$$B+        +&$$b,        _@$$B$$$z      ;#$$8%$$Z.         +$$$M:                   
 *      !&$$b^      !*$$#!         C$$$\k$$M:    .Q$$@}X$$8!         ,w$$$bc|}-~<iI".         
 *       f$$$x     :k$$&+         _B$$p./$$$x    /$$$u +@$$x          '[YdW@$$$$$$$%oOr>      
 *       'w$$%~   ^w$$B}         `b$$@- "h$$Wl  _8$$O' 'p$$o"             ^:!><+](n0#$$@Z>    
 *        >8$$b^ 'L$$$\          x$$$C   )$$$C Io$$a;   ($$$t                       `[#$$*:   
 *         /$$$X.c$$$x          <8$$&l   .Z$$@\w$$%+    "a$$#;     ,]]"               p$$$>   
 *         .J$$@w$$$Y.         .O$$$n     >8$$$$$$t      \$$$J     0$$*\"         '!(p$$$u.   
 *          "d$$$$$Q'          >B$$%i      r$$$$$L.      ^a$$@{    _b$$$&qJvnnncCq#$$$&Q-     
 *           lh$$$Y'           [$$$U       `0$$@C^        {@$$a^    .+jQk&@$$$$$@&aOn[:       
 *            :\r]             '{x)^        .+}>           ?UJ).         ^:l>>>l:^.            
 *                                                                                           
 * Copyright (C) 2022 - 2023, HaoQing, <970407688@qq.com>.
 * <https://github.com/wuxiaolie/VisitorMS> & <https://gitee.com/yang-haoqing/visitor-ms.git>
 *
 * This software is licensed as described in the file COPYING, which you should have received 
 * as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell copies of 
 * the Software, and permit persons to whom the Software is furnished to do so, under 
 * the terms of the COPYING file.
 *
 *********************************************************************************************/

package com.example.smarthome;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
public class MainActivity extends Activity {
	Button kct;
	Button gct;
	Button kws;
	Button gws;
	Button kel;
	Button gel;
	Button kys;
	Button gys;
	Button ljms;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		     
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		  setContentView(R.layout.activity_main);
        WebView wb = (WebView) findViewById(R.id.web);
        wb.setWebViewClient(new WebViewClient());
        String s="http://192.168.3.143:8080/?action=stream";
        wb.loadUrl(s);
         
    	kct=(Button)findViewById(R.id.kct);
    	gct=(Button)findViewById(R.id.gct);
    	kws=(Button)findViewById(R.id.kws);
    	gws=(Button)findViewById(R.id.gws);
    	kel=(Button)findViewById(R.id.kel);
    	gel=(Button)findViewById(R.id.gel);
    	kys=(Button)findViewById(R.id.kys);
    	gys=(Button)findViewById(R.id.gys);
    	ljms=(Button)findViewById(R.id.ljms);
    	    	
    	kct.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
			  new NetUtils("open1").sendMessage();
			}
		});
    	gct.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("close1").sendMessage();
			}
		});
    	kws.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("open2").sendMessage();
			}
		});
    	gws.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("close2").sendMessage();
			}
		});
    	kel.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("open1").sendMessage();
			}
		});
    	gel.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("close1").sendMessage();
			}
		});
    	kys.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("close2").sendMessage();
			}
		});
    	gys.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("open2").sendMessage();
			}
		});
    	ljms.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				 new NetUtils("123312").sendMessage();
			}
		});
    }}
