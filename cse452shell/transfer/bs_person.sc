camera [
eye 2 1 -5
look -0.4 -0.2 1
up 0 1 0
angle 80
near-far 3 20
]

light [
position 1 4 -6
color 1 1 1
]

mastersubgraph piece [
	trans [
		object cube [
		]
	]
]

mastersubgraph head [
	trans [
		scale 0.35 0.2 0.2
		translate 0 -1.4 -0.3
		subgraph piece
	]

	trans [
		scale 0.35 0.35 0.35
		subgraph piece
	]
]

mastersubgraph leg [
	trans [
		scale 0.2 0.7 0.2
		subgraph piece
	]

	trans [
		translate 0 -0.8 0
		scale 0.2 0.7 0.2
		subgraph piece
	]

	trans [
		translate 0 -1.3 -0.25
		scale 0.2 0.2 0.5
		subgraph piece
	]
]

mastersubgraph arm [
	trans [
		scale 0.4 0.25 0.35
		subgraph piece
	]

	trans [
		scale 0.2 0.7 0.2
		translate 0.5 -0.75 0
		subgraph piece
	]

	trans [
		scale 0.2 0.7 0.2
		translate 0.5 -1.9 0
		subgraph piece
	]
]

mastersubgraph torso [
	trans [
		scale 0.75 0.25 0.35
		subgraph piece
	]

	trans [
		scale 0.75 0.25 0.35
		translate 0 1.25 0
		subgraph piece
	]

	trans [
		scale 0.95 0.25 0.35
		translate 0 2.5 0
		subgraph piece
	]

	trans [
		translate 0.6 1 0
		subgraph arm
	]

	trans [
		rotate 0 1 0 180
		translate 0.6 1 0
		subgraph arm
	]
]

mastersubgraph body [
	trans [
		subgraph torso
	]

	trans [
		translate 0.25 -0.6 0
		subgraph leg
	]

	trans [
		translate -0.25 -0.6 0
		subgraph leg
	]

	trans [
		translate 0 1.6 0
		subgraph head
	]
]


mastersubgraph root [
	trans [
		subgraph body
	]
]

