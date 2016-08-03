class Solution {
  static class TrieNode {
       TrieNode[] next;
       int index;
       List<Integer> list; // is palindrome if we don't consider suffix
          
      TrieNode() {
         next = new TrieNode[26];
         index = -1;
         list = new ArrayList<>();
      }
  }

  private boolean isPalindrome(String word, int i, int j) {
    while (i < j) {
      if (word.charAt(i++) != word.charAt(j--)) return false;
    }
    
    return true;
  }

  public List<List<Integer>> palindromePairs(String[] words) {
    List<List<Integer>> res = new ArrayList<>();
    
    TrieNode root = new TrieNode();
    
    for (int i = 0; i < words.length; i++) {
      addWord(root, words[i], i);
    }
    
    for (int i = 0; i < words.length; i++) {
      search(words, i, root, res);
    }
    
    return res;
  }

  private void addWord(TrieNode root, String word, int index) {
    for (int i=word.length()-1; i>=0; --i) {
      if (root.next[word.charAt(i) - 'a'] == null) {
        root.next[word.charAt(i) - 'a'] = new TrieNode();
      }
      if (isPalindrome(word, 0, i)) {
        root.list.add(index);
      }
      root = root.next[word.charAt(i)-'a'];
    }      

    root.list.add(index); //empty string is certainly a palindrone
    root.index = index; 
  }

  void search(String[] words, int i, TrieNode root, List<List<Integer>> ans) {
    for (int j=0; j<words[i].length(); ++j) {
      if (root.index != -1 && root.index != i && isPalindrome(words[i], j, words[i].length()-1)) {
        ans.add(Arrays.asList(i, root.index));
      }
      root = root.next[words[i].charAt(j) - 'a'];
      if (root == null) return; 
    }

    for (int j : root.list) {
      if (i == j) continue; 
      ans.add(Arrays.asList(i, j));
    }
  } 
}
