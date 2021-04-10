## 동적 배열(Dynamic array)
배열의 큰 문제 중 하나는 처음에 배열을 선언할 때, 배열의 크기를 지정해야 하며,
그 이상의 자료는 집어넣을 수 없다는 점이다. 이와 같은 문제를 해결하기 위해 고안된 것이 자료의 개수가 변함에 따라 크기가 변동되는
동적 배열(Dynamic array) 이다.

아래는 동적배열이 가지는 특성이다.
* 배열의 크기를 변경하는 resize() 연산이 가능하다. 이 동작을 수행하는 데는 배열의 크기 N에 비례하는 시간이 걸린다.
* 주어진 원소를 배열의 맨 끝에 추가함으로써 크기를 1 늘리는 append() 연산을 지원한다. 이 동작을 수행하는 데는 상수시간이 걸린다.

### 동적배열의 재할당 전략
아래 코드를 보자.
```c
if(size == capacity){
  int newCapacity = capacity + M;
  int * newArray = (int*)malloc(sizeof(int) * newCapacity);
  
  for(int i=0; i<capacity; i++)
    newArray[i] = array[i];
}
```
위 코드는 상수시간에 append() 연산을 수행하다가, 배열의 크기가 꽉차는 순간,
배열의 크기에 비례하는 시간복잡도를 가닌 resize()연산을 하는 코드이다.


