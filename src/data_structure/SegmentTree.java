package data_structure;

public class SegmentTree {
	class Node{
		int min;
		int start;
		int end;
		Node left;
		Node right;
		public Node(int min, int start, int end){
			this.min = min;
			this.start = start;
			this.end = end;
		}
	}
	
	private Node root;
	
	public Node build(int[] nums,int start, int end){
		if (start > end){
			return null;
		}
		root = new Node(Integer.MAX_VALUE, start, end);
		if (start != end){
			int mid = start + (end - start) / 2;
			root.left = build(nums, start, mid);
			root.right = build(nums,mid + 1, end);
			root.min = Math.min(root.left.min, root.right.min);
		} else {  // leaf node
			root.min = nums[start];
		}
		return root;
	}
	
	public void update(Node root, int index, int val){
		if(root == null){
			return;
		}
		// leaf node
		if(root.start == index && root.end == index){
			root.min = val;
		}
		int mid = root.start + (root.end - root.start) / 2;
		if(index <= mid){
			update(root.left, index, val);
		}
		if(index > mid){
			update(root.right, index, val);
		}
		
		root.min = Math.min(root.left.min, root.right.min);
	}
	
	public int query(Node root, int start, int end){
		if(root == null || root.start > end || root.end < start){
			return Integer.MAX_VALUE;
		}
		// leaf node
		if(start == root.start && end == root.end){
			return root.min;
		}
		int mid = root.start + (root.end - root.start) / 2;
		int leftmin = Integer.MAX_VALUE, rightmin = Integer.MAX_VALUE;
		if(start <= mid){
			if(end <= mid){
				leftmin = query(root.left, start, end);
			} else{
				leftmin = query(root.left, start, mid);
			}
		}
		if(mid < end){
			if (start > mid){
				rightmin = query(root.right,start,end);
			} else{
				rightmin= query(root.right,mid + 1,end);
			}
		}
		return Math.min(leftmin, rightmin);
	}
}
