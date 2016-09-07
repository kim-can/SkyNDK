package sky.skyndk;

import android.os.Bundle;
import android.widget.TextView;

import butterknife.BindView;
import butterknife.ButterKnife;
import jc.sky.core.Impl;
import jc.sky.view.SKYActivity;
import jc.sky.view.SKYBuilder;

/**
 * @创建人 sky
 * @创建时间 16/9/7 上午10:17
 * @类描述 一句话描述你的UI
 */
public class MainActivity extends SKYActivity<IMainBiz> implements IMainActivity {

	static {
		System.loadLibrary("skyNDK");
	}

	@BindView(R.id.tv_content) TextView tvContent;

	@Override protected SKYBuilder build(SKYBuilder skyBuilder) {
		skyBuilder.layoutId(R.layout.activity_main);
		return skyBuilder;
	}

	@Override protected void initData(Bundle bundle) {
		tvContent.setText(getSkyNDKText());
	}

	// 声明一个本地方法，用native关键字修饰
	public native String getSkyNDKText();

}

@Impl(MainActivity.class)
interface IMainActivity {

}