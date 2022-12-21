void light(bool a){
  if(a){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
}
