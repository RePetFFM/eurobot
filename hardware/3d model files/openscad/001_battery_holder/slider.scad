$fn = 32;

base_rad = 5.8/2;
base_length = 80;
base_height = 8;

screw_head_rad = 7/2;
screw_head_height = 3.4; 
screw_m3_rad = 3.4/2;



difference() {
	hull() {
		translate([base_length/2,0,0]) cylinder(r=base_rad,base_height);
		translate([-base_length/2,0,0]) cylinder(r=base_rad,base_height);	
	}	

	translate([base_length/2-10,0,base_height-3.2]) m3screw(10);
	translate([0,0,base_height-3.2]) m3screw(10);
	translate([-base_length/2+10,0,base_height-3.2]) m3screw(10);
}


module m3screw(screw_length) {
	translate([0,0,-screw_length]) cylinder(r=screw_m3_rad,screw_length+0.1);
	cylinder(r=screw_head_rad,screw_head_height);
}
