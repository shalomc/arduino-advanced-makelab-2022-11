# Remarks on the included code
## ToggleButton and ToggleButton2
Usually we want code to be readable. Sometimes we make it less readable to meet constraints. 

These 2 sketches toggle a switch state between on and off. Each click will change the state. 
Both sketches are almost identical. 

To toggle the switch state, `ToggleButton` uses this terse code
```
  if (button_value == LOW ) {            // check if the input is HIGH
    is_turned_on = !is_turned_on; 
    digitalWrite(ledPin, is_turned_on);
  }
```
`ToggleButton2`	uses the following code, which appears to be more readable
```
  if (button_value == LOW ) {            // check if the input is HIGH
    if (is_turned_on) { 
      is_turned_on = false ;
    } else {
      is_turned_on = true ;
    }
    if (is_turned_on) {
      digitalWrite(ledPin, HIGH);  // turn LED ON
    } else {
      digitalWrite(ledPin, LOW);   // turn LED OFF
    }
  }
```
There is a small difference is in the program size after compilation. The terse program uses 30 bytes less. This is not important in our case, but sometimes it will be critical. 

`ToggleButton`: Sketch uses 1128 bytes (3%) of program storage space. Maximum is 30720 bytes. 

`ToggleButton2`: Sketch uses 1158 bytes (3%) of program storage space. Maximum is 30720 bytes. 



## fade 
![Sine waves](../images/TrafficLight-02-fade-image-01.png "Pure sine waves")