Simple concurrent hashmap implementation.

## ref
* https://preshing.com/20130529/a-lock-free-linear-search/

## step
* バケットの拡張なし、(hash後の)keyのダブリなし縛り
* バケットの拡張なし、(hash後の)keyのダブリなし縛りで、削除のsupport
  * 
* バケット拡張なし、(hash後の)key ダブリあり.
  * 同じkeyの要素に対して、同時にその要素に対する削除
