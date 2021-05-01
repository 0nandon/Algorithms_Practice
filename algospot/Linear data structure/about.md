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

위 코드는 한번 재할당 할 때마다, 배열의 크기를 M씩 늘렸다. 만약 N개의 숫자를 배열에 저장한다고 했을 때,
배열의 크기를 M씩 늘려나간 다면, 전체 복사하는 원소의 수는 다음과 같다.

> ((K + 1) * K / 2) * M = O(K^2) = O(N^2), ((K = M / N)

N번의 append()연산을 하는데 O(N^2) 시간이 걸린다면, 평균적으로 한번의 append() 연산을 하는 데, O(N)이 걸린다.

그렇다면, 배열의 크기를 늘릴 때, M씩 늘리는게 아니라, i번 재할당 시, 2^i 크기로 배열의 크기를 늘리면 어떻게 될까?

> 재할당 수 : 2^0 + 2^1 + 2^2 + ... + 2^(k-1) + 2^k = (2^k - 1) + 2^k = O(N), (2^k >= N)

N번의 append() 연산을 하는데 O(N) 시간이 걸린다면, 평균적으로 한번의 append() 연산을 하는 데, 상수시간이 걸리게 된다.
즉, 동적배열에 있어 상수시간에 append() 연산을 수행할 수 있게 된 것이다.

