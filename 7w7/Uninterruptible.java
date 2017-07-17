
public class Uninterruptible {

	public static void main(String[] args) throws InterruptedException {

		final Object o1 = new Object(); final Object o2 = new Object();

		Thread t1 = new Thread() {
			public void run() {
				try {
					synchronized(o1) {
						Thread.sleep(1000);
						synchronized(o2) {}
					}
				} catch (InterruptedException e) { System.out.println("t1 interrupted"); }
			}
		};

		Thread t2 = new Thread() {
			public void run() {
				try {
					synchronized(o2) {
						Thread.sleep(1000);
						synchronized(o1) {}
					}
				} catch (InterruptedException e) { System.out.println("t2 interrupted"); }
			}
		};

		t1.start(); 
		t2.start();
		Thread.sleep(2000);
		t1.interrupt(); 
		t2.interrupt();
		t1.join(); t2.join();
	}
}
//终止线程的最终手段是让run()函数返回（可能是通过抛出InterruptedException）。不过，如果你的线程由于等待内置锁而陷入死锁，且不能中断其等待锁的状态，那么要终止死锁线程就只剩下终止JVM运行这条路了。