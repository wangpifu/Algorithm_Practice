package learned;
/*
 * Two threads, two locks. 
 * The first thread runs a loop that attempts to acquire the locks in a certain order, 
 * the second thread runs a loop that attempts to acquire the locks in the opposite order. 
 * Each thread releases both locks after successfully acquiring the locks.
 */
public class MyDeadlock {
	static class Locker implements Runnable{
		private Object first, second;
		
		public Locker(Object first, Object second){
			this.first = first;
			this.second  = second;
		}
		
		@Override
		public void run(){
			while(true){
				synchronized(first){
					synchronized(second){
						System.out.println(Thread.currentThread().getName());
					}
				}
			}
		}
	}
	
	public static void main(String[] args){
		Object locker1 = new Object();
		Object locker2 = new Object();
		new Thread(new Locker(locker1,locker2), "thread 1").start();
		new Thread(new Locker(locker2,locker1), "thread 2").start();

;	}
}
