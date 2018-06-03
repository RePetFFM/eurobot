$fn = 64;

pcb_screw_hole_dist = 56-3.5;

difference() {
	hull() {
		translate([-73/2,0,0]) cylinder(r=5,10);
		translate([73/2,0,0]) cylinder(r=5,10);	
	}

	translate([pcb_screw_hole_dist/2,0,-1]) cylinder(r=3.5/2,20);
	translate([-pcb_screw_hole_dist/2,0,-1]) cylinder(r=3.5/2,20);

	translate([-73/2,0,6.8]) cylinder(r=3,3.3);
	translate([73/2,0,6.8]) cylinder(r=3,3.3);	

	translate([-73/2,0,-1]) cylinder(r=3.5/2,10);
	translate([73/2,0,-1]) cylinder(r=3.5/2,10);

	translate([pcb_screw_hole_dist/2,0,1.5])
	hull() {
		cube(size=[6.1/2,6.1,3.5],center=true);
		rotate([0,0,60]) cube(size=[6.5/2,6.5,3.5],center=true);
		rotate([0,0,-60]) cube(size=[6.5/2,6.5,3.5],center=true);
	}

	translate([-pcb_screw_hole_dist/2,0,1.5])
	hull() {
		cube(size=[6.1/2,6.1,4],center=true);
		rotate([0,0,60]) cube(size=[6.5/2,6.5,4],center=true);
		rotate([0,0,-60]) cube(size=[6.5/2,6.5,4],center=true);
	}
	
}
