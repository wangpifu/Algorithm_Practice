package data_structure;

/* 
 * Weighted quick union with compressed path
 * time complexity is O(N + Mlog*N) where log*N is no bigger than 5
 * N objects with M union-find operations,so it is almost linear
 */
public class WQUCP {
	private int[] root;  // record root
	private int[] size;  // record weight of curt node as root of tree
	public WQUCP(int n){
		root = new int[n];
		size = new int[n];
		for(int i = 0; i < n; i++){
			root[i] = i;
			size[i] = 1;
		}
	}
	
	public int getRoot(int i){
		while(root[i] != i){
			// path compression, make curt node points to its grandparent
			root[i] = root[root[i]];
			i = root[i];
		}
		return i;
	}
	
	public boolean isConnected(int i, int j){
		return getRoot(i) == getRoot(j);
	}
	
	public void union(int p, int q){
		int root_p = getRoot(p);
		int root_q = getRoot(q);
		// link root of smaller tree to root of larger tree
		if(size[root_p] < size[root_q]){
			root[root_p] = root_q;
			size[root_q] += size[root_p];
		} else {
			root[root_q] = root_p;
			size[root_p] += size[root_q];
		}
	}
	
	public void status(){
		System.out.println("For test,current root array is : ");
		for(int i = 0; i < root.length; i++){
			System.out.print(root[i]);
		}
		System.out.println();
	}	
}
