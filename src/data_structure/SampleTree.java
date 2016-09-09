package data_structure;

import data_structure.TreeNode;
//this class is only used to build a tree for test.
//tree implement is in TreeNode class
/*
*                       4
*                  2        6
*               1    3   5      7
*/
public class SampleTree {
	public TreeNode root;
	public SampleTree(){
		TreeNode left1 = new TreeNode(1);
		TreeNode right1 = new TreeNode(3);
		TreeNode parent1 = new TreeNode(2);
		left1.parent = parent1;
		right1.parent = parent1;
		parent1.left = left1;
		parent1.right = right1;
		
		TreeNode left2 = new TreeNode(5);
		TreeNode right2 = new TreeNode(7);
		TreeNode parent2 = new TreeNode(6);
		left2.parent = parent2;
		right2.parent = parent2;
		parent2.left = left2;
		parent2.right = right2;
		
		root = new TreeNode(4);
		root.left = parent1;
		root.right = parent2;
		parent1.parent = root;
		parent2.parent = root;
		
	}
	// return this built tree root
	public TreeNode getRoot(){
		return root;
	}
}

