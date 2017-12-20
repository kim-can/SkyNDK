package sky.skyndk;

import jc.sky.SKYApplication;
import retrofit2.Retrofit;
import sky.core.SKYPlugins;

/**
 * @创建人 sky
 * @创建时间 16/9/7 上午10:39
 * @类描述
 */
public class SkyNDKApplication extends SKYApplication {

	@Override public boolean isLogOpen() {
		return true;
	}

	@Override public Retrofit.Builder httpAdapter(Retrofit.Builder builder) {
		builder.baseUrl("http://www.baidu.com");
		return builder;
	}

	@Override public SKYPlugins.Builder pluginInterceptor(SKYPlugins.Builder builder) {
		return builder;
	}

	@Override public int layoutLoading() {
		return 0;
	}

	@Override public int layoutEmpty() {
		return 0;
	}

	@Override public int layoutBizError() {
		return 0;
	}

	@Override public int layoutHttpError() {
		return 0;
	}
}
