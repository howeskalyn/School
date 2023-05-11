#include "colors.inc"
#include "stones.inc"       
#include "woods.inc" 
#include "shapes.inc"

camera {         
  location <5, 5, 3>
  look_at <0, 0, 0>                
  angle 50
}

//light_source { <2, 10, 5> color White }
light_source { <-10, 15, 10> color White spotlight radius 10 falloff 20}

plane { <0, 1, 0>, -1
  texture {
    T_Wood14
    scale 5
    finish { phong 0.75 }
  }
  finish { ambient 0.1 diffuse 0.4 }
}   

// shallow box for tiles
object {Round_Box (<-6,-0.9,-4>,<2,-1,3>, 0.04 , 0)   
  texture {
    T_Stone22
    scale 3  
    finish { phong 0.75 }
  }
} 

// text variables
#declare firstLine = text {
    ttf "timrom.ttf" "Computer"
	0.7, 0

  rotate -90*y
  rotate 90*z
  scale 0.4
  translate <-3.2,0.5,-0.8>
  texture {
    T_Stone10
    finish { phong 0.75 }
    }
  }   
  
#declare secondLine = text {
    ttf "timrom.ttf" "Graphics"
	0.7, 0

  rotate -90*y
  rotate 90*z
  scale 0.4
  translate <-2.8,0.5,-0.8>
  texture {
    T_Stone10
    finish { phong 0.75 }
    }
  } 
  
#declare rip = text {
    ttf "timrom.ttf" "R.I.P."
	1, 0

  rotate -90*y
  rotate 90*z
  scale 0.7
  translate <-2,0.5,-0.8>
  texture {
    T_Stone10
    finish { phong 0.75 }
    }
  } 

#declare date1 = text {
    ttf "timrom.ttf" "Jan 31, 2022"
	0.5, 0

  rotate -90*y
  rotate 90*z
  scale 0.25
  translate <-1.5,0.5,-0.6>
  texture {
    T_Stone10
    finish { phong 0.75 }
    }
  } 
  
#declare date2 = text {
    ttf "timrom.ttf" "May 20, 2022"
	0.5, 0

  rotate -90*y
  rotate 90*z
  scale 0.25
  translate <-1.1,0.5,-0.7>
  texture {
    T_Stone10
    finish { phong 0.75 }
    }
  }

  
// engraved coffin 
difference  {  

// lid
object {Round_Box (<1,0.4,1>,<-4,-0.08,-1>, 0.05 , 0)  
         
        texture{ T_Stone17
                 finish { phong 0.75}
                }
      } 

object {firstLine} 
object {secondLine} 
object {rip} 
object {date1}
object {date2}

}
 
//coffin
object {Round_Box (< 1, 0, 1>, <-4, -5, -1> , 0.05, 0) 
  texture {
    T_Stone17    
    finish { phong 0.75 }                                 
    }
}
