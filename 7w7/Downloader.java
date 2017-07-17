import java.net.URL;
import java.io.*;
import java.util.ArrayList;

class Download {

	public static void main(String[] args) throws Exception {
		URL from = new URL("http://www.7-zip.org/a/7z1700.exe");
		Downloader downloader = new Downloader(from, "download.out");
		downloader.start();
		downloader.addListener(new ProgressListener() {
			public void onProgress(int n) { System.out.print("\r"+n); System.out.flush(); }
			public void onComplete(boolean success) {}
		});
		downloader.join();
	}
}

class Downloader extends Thread {
	private InputStream in;
	private OutputStream out;
	private ArrayList<ProgressListener> listeners;

	public Downloader(URL url, String outputFilename) throws IOException {
		in = url.openConnection().getInputStream();
		out = new FileOutputStream(outputFilename);
		listeners = new ArrayList<ProgressListener>();
	}
	public synchronized void addListener(ProgressListener listener) {
		listeners.add(listener);
	}
	public synchronized void removeListener(ProgressListener listener) {
		listeners.remove(listener);
	}
	private synchronized void updateProgress(int n) {
		//保护性复制
		ArrayList<ProgressListener> listenersCopy;
			synchronized(this) {
				listenersCopy = (ArrayList<ProgressListener>)listeners.clone();
			}
			for (ProgressListener listener: listenersCopy)
				listener.onProgress(n);
	}

	public void run() {
		int n = 0, total = 0;
		byte[] buffer = new byte[1024];

		try {
			while((n = in.read(buffer)) != -1) {
				out.write(buffer, 0, n);
				total += n;
				updateProgress(total);
			}
			out.flush();
		} catch (IOException e) { e.printStackTrace();  }
	}
}

interface ProgressListener {
	void onProgress(int current);
}

