import processing.serial.*;


// String that is held in "led.txt". This is a simple bitstring
String[] ledLines;
boolean[] lights;
int w, h;

Serial myPort;

void setup()
{
  
  w = 480;
  h = 270;
  size(480, 270);
  background(255);
  
  lights = new boolean[3];
  
  myPort = new Serial(this, "COM6", 9600);
  
}// end setup()


void draw()
{

  clear();
  background(255);
  
  // Load the line held by led.txt into ledLines, then move that into ledLine
  // led.txt is just a simple string of three 0's or 1's. Examples: "101", "110", "000", "111"
  ledLines = loadStrings("led.txt");
  
  // Set all light booleans to false
  for(int i = 0; i < lights.length; i++) {
    lights[i] = false;
  }
  
  // For each of the 3 characters, print whether it's "on"
  // A lowercase r, g, b indicates the light is to be turned off,
  // while an uppercase indicates the light is to be turned on.
  if (ledLines[0].charAt(0) == '1') {
  
    print('R');
    myPort.write('R');
    lights[0] = true;
  
  }else{
  
    myPort.write('r');
  
  }
  if (ledLines[0].charAt(1) == '1') {
  
    print('G');
    myPort.write('G');
    lights[1] = true;
  
  }else{
  
    myPort.write('g');
  
  }
  if (ledLines[0].charAt(2) == '1') {
  
    print('B');
    myPort.write('B');
    lights[2] = true;
  
  }else{
  
    myPort.write('b');
  
  }
  println();
  println();
  
  // Draw some cute little circles on the screen if a light is on
  for(int i = 0; i < lights.length; i++) {
  
    stroke(0);
    noFill();
    
    circle(90 + i * (w - 32) / lights.length, h / 2, 128);
    
    if (lights[i]) {
      
      noStroke();
      
      switch(i) {
       
        case 0: fill(255, 0, 0); break;
        case 1: fill(0, 255, 0); break;
        case 2: fill(0, 0, 255); break;
        default: noFill();
        
      }
      
      circle(90 + i * (w - 32) / 3, h / 2, 96);
      
    }
  
  }
  
  // Delay for 2 seconds. It would be absurd to do it at every instance, and possibly would cause problems
  delay(500);

}// end draw()
