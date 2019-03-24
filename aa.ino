mrpwm=mrs+corr;
         mlpwm=mls-corr;
      if(mlpwm>254) mlpwm=254;
      if(mrpwm>254) mrpwm=254;
      if(mlpwm<0) {
        mlpwm=(-1)*mlpwm;
        digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      if(mrpwm<0) {
        mrpwm=(-1)*mrpwm;
        if(mrpwm>254) mrpwm=254;
        digitalWrite(mrf,LOW);
      digitalWrite(mlf,HIGH);
      digitalWrite(mrb,HIGH);
      digitalWrite(mlb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
        }
      if(mlpwm>0 && mrpwm>0){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
