int solution(){
	int answer = 0;
	while(1){
		answer++; n--;
		if(answer%m == 0) n++;
		if(n == 0) break;
	}

	return answer;
}
