$fn = 32;

battery_width = 66;
slider_base_length = 80;
top_plate_height = 6;
nut_width = 6;
screw_m3_rad = 3.5/2;

difference() {
	cube(size=[battery_width,slider_base_length,top_plate_height],center=true);

	translate([-battery_width/2-0.1,slider_base_length/2-10,0])rotate([0,90,0]) cylinder(r=screw_m3_rad,20);
	translate([-battery_width/2-0.1,0,0])rotate([0,90,0]) cylinder(r=screw_m3_rad,20);
	translate([-battery_width/2-0.1,-slider_base_length/2+10,0])rotate([0,90,0]) cylinder(r=screw_m3_rad,20);	

	mirror(v=[1,0,0]) {
		translate([-battery_width/2-0.1,slider_base_length/2-10,0])rotate([0,90,0]) cylinder(r=screw_m3_rad,20);
		translate([-battery_width/2-0.1,0,0])rotate([0,90,0]) cylinder(r=screw_m3_rad,20);
		translate([-battery_width/2-0.1,-slider_base_length/2+10,0])rotate([0,90,0]) cylinder(r=screw_m3_rad,20);
	}

	translate([0,slider_base_length/5,0]) cutout();
	translate([0,-slider_base_length/5,0]) cutout();

	translate([battery_width/2-6,slider_base_length/2-10,0]) cube(size=[3.5,nut_width,10],center=true);
	translate([battery_width/2-6,0,0]) cube(size=[3.5,nut_width,10],center=true);
	translate([battery_width/2-6,-slider_base_length/2+10,0]) cube(size=[3.5,nut_width,10],center=true);
	
	mirror(v=[1,0,0]) {
		translate([battery_width/2-6,slider_base_length/2-10,0]) cube(size=[3.5,nut_width,10],center=true);
		translate([battery_width/2-6,0,0]) cube(size=[3.5,nut_width,10],center=true);
		translate([battery_width/2-6,-slider_base_length/2+10,0]) cube(size=[3.5,nut_width,10],center=true);
	}
}

module cutout() {
	hull() {
		translate([battery_width/2-15,0,-5]) cylinder(r=10,10,$fn=64);
		translate([-battery_width/2+15,0,-5]) cylinder(r=10,10,$fn=64);
	}
	
}
