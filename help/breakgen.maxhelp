{
	"patcher": {
		"fileversion": 1,
		"appversion": {
			"major": 9,
			"minor": 1,
			"revision": 0,
			"architecture": "x64",
			"modernui": 1
		},
		"classnamespace": "box",
		"rect": [
			100.0,
			100.0,
			680.0,
			600.0
		],
		"bglocked": 0,
		"openinpresentation": 0,
		"default_fontsize": 13.0,
		"default_fontface": 0,
		"default_fontname": "Arial",
		"gridonopen": 1,
		"gridsize": [
			15.0,
			15.0
		],
		"gridsnaponopen": 1,
		"objectsnaponopen": 1,
		"statusbarvisible": 2,
		"toolbarvisible": 1,
		"lefttoolbarpinned": 0,
		"toptoolbarpinned": 0,
		"righttoolbarpinned": 0,
		"bottomtoolbarpinned": 0,
		"toolbars_unpinned_last_save": 0,
		"tallnewobj": 0,
		"boxanimatetime": 200,
		"enablehscroll": 1,
		"enablevscroll": 1,
		"devicewidth": 0.0,
		"description": "",
		"digest": "Generate tempo multipliers and breakpoint files for modmetro~",
		"tags": "",
		"style": "",
		"subpatcher_template": "",
		"showontab": 0,
		"assistshowspatchername": 0,
		"boxes": [
			{
				"box": {
					"maxclass": "jsui",
					"filename": "helpname.js",
					"jsarguments": [
						"breakgen"
					],
					"patching_rect": [
						10.0,
						10.0,
						305.0,
						55.0
					],
					"border": 0,
					"ignoreclick": 1,
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [
						""
					],
					"parameter_enable": 0,
					"id": "top-1"
				}
			},
			{
				"box": {
					"fontname": "Arial",
					"fontsize": 13.0,
					"maxclass": "newobj",
					"text": "js helpstarter breakgen",
					"patching_rect": [
						470.0,
						30.0,
						165.0,
						23.0
					],
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [
						""
					],
					"saved_object_attributes": {
						"filename": "helpstarter",
						"parameter_enable": 0
					},
					"id": "top-2"
				}
			},
			{
				"box": {
					"fontname": "Arial",
					"fontsize": 13.0,
					"maxclass": "newobj",
					"text": "p basic",
					"patching_rect": [
						10.0,
						85.0,
						80.0,
						23.0
					],
					"numinlets": 0,
					"numoutlets": 0,
					"outlettype": [],
					"patcher": {
						"fileversion": 1,
						"appversion": {
							"major": 9,
							"minor": 1,
							"revision": 0,
							"architecture": "x64",
							"modernui": 1
						},
						"classnamespace": "box",
						"rect": [
							100.0,
							126.0,
							680.0,
							574.0
						],
						"bglocked": 0,
						"openinpresentation": 0,
						"default_fontsize": 13.0,
						"default_fontface": 0,
						"default_fontname": "Arial",
						"gridonopen": 1,
						"gridsize": [
							15.0,
							15.0
						],
						"gridsnaponopen": 1,
						"objectsnaponopen": 1,
						"statusbarvisible": 2,
						"toolbarvisible": 1,
						"lefttoolbarpinned": 0,
						"toptoolbarpinned": 0,
						"righttoolbarpinned": 0,
						"bottomtoolbarpinned": 0,
						"toolbars_unpinned_last_save": 0,
						"tallnewobj": 0,
						"boxanimatetime": 200,
						"enablehscroll": 1,
						"enablevscroll": 1,
						"devicewidth": 0.0,
						"description": "",
						"digest": "",
						"tags": "",
						"style": "",
						"subpatcher_template": "",
						"showontab": 1,
						"assistshowspatchername": 0,
						"boxes": [
							{
								"box": {
									"maxclass": "jsui",
									"filename": "helpdetails.js",
									"jsarguments": [
										"breakgen",
										85
									],
									"patching_rect": [
										10.0,
										10.0,
										650.0,
										125.0
									],
									"border": 0,
									"ignoreclick": 1,
									"numinlets": 1,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"parameter_enable": 0,
									"id": "basic-1"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "step",
									"patching_rect": [
										26.0,
										145.0,
										40.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "basic-2"
								}
							},
							{
								"box": {
									"maxclass": "button",
									"patching_rect": [
										30.0,
										170.0,
										24.0,
										24.0
									],
									"numinlets": 1,
									"numoutlets": 1,
									"outlettype": [
										"bang"
									],
									"parameter_enable": 0,
									"id": "basic-3"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "100 steps",
									"patching_rect": [
										80.0,
										145.0,
										70.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "basic-4"
								}
							},
							{
								"box": {
									"maxclass": "button",
									"patching_rect": [
										90.0,
										170.0,
										24.0,
										24.0
									],
									"numinlets": 1,
									"numoutlets": 1,
									"outlettype": [
										"bang"
									],
									"parameter_enable": 0,
									"id": "basic-5"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "uzi 100",
									"patching_rect": [
										90.0,
										205.0,
										60.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 3,
									"outlettype": [
										"bang",
										"bang",
										"int"
									],
									"id": "basic-6"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "waveform",
									"patching_rect": [
										190.0,
										145.0,
										80.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "basic-7"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "umenu",
									"items": [
										"sine",
										",",
										"triangle",
										",",
										"square",
										",",
										"saw",
										"down",
										",",
										"saw",
										"up",
										",",
										"constant"
									],
									"patching_rect": [
										190.0,
										170.0,
										110.0,
										23.0
									],
									"numinlets": 1,
									"numoutlets": 3,
									"outlettype": [
										"int",
										"",
										""
									],
									"parameter_enable": 0,
									"id": "basic-8"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "prepend wavetype",
									"patching_rect": [
										190.0,
										205.0,
										112.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "basic-9"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "speed: one cycle = sr / freq steps",
									"patching_rect": [
										340.0,
										145.0,
										230.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "basic-10"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "freq 100",
									"patching_rect": [
										340.0,
										170.0,
										62.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "basic-11"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "freq 400",
									"patching_rect": [
										410.0,
										170.0,
										62.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "basic-12"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "sr 10000",
									"patching_rect": [
										340.0,
										205.0,
										66.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "basic-13"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "sr 2500",
									"patching_rect": [
										414.0,
										205.0,
										58.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "basic-14"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "constant level",
									"patching_rect": [
										570.0,
										145.0,
										100.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "basic-15"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "constval 1.25",
									"patching_rect": [
										570.0,
										170.0,
										92.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "basic-16"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "breakgen",
									"patching_rect": [
										30.0,
										265.0,
										64.0,
										23.0
									],
									"numinlets": 1,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "basic-17"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "flonum",
									"patching_rect": [
										30.0,
										305.0,
										70.0,
										23.0
									],
									"numinlets": 1,
									"numoutlets": 2,
									"outlettype": [
										"",
										"bang"
									],
									"parameter_enable": 0,
									"format": 6,
									"id": "basic-18"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "multiplier for the next beat",
									"patching_rect": [
										106.0,
										304.0,
										190.0,
										25.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"bubble": 1,
									"id": "basic-19"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "zl.stream 100",
									"patching_rect": [
										30.0,
										345.0,
										92.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 2,
									"outlettype": [
										"",
										""
									],
									"id": "basic-20"
								}
							},
							{
								"box": {
									"maxclass": "multislider",
									"patching_rect": [
										30.0,
										377.0,
										330.0,
										130.0
									],
									"numinlets": 1,
									"numoutlets": 2,
									"outlettype": [
										"",
										""
									],
									"parameter_enable": 0,
									"size": 100,
									"settype": 1,
									"setminmax": [
										0.0,
										2.0
									],
									"ignoreclick": 1,
									"id": "basic-21"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "the last 100 values, from 0.0 (bottom) to 2.0 (top)",
									"patching_rect": [
										30.0,
										512.0,
										330.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "basic-22"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "modmetro~ multiplies the length of each beat by one of these values: 1.0 leaves the beat alone, above 1.0 makes it longer (slower) and below 1.0 shorter (faster).\n\nOne waveform cycle takes sr / freq steps, so the defaults (sr 10000, freq 100) make one slow swing every 100 beats. Sending sr also restarts the cycle.\n\nThe waveforms swing the full 0.0 to 2.0. To keep beats within, say, 20% of the tempo, write the values with writefile's depth argument (see the write tab).",
									"patching_rect": [
										385.0,
										290.0,
										275.0,
										230.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 14,
									"id": "basic-23"
								}
							}
						],
						"lines": [
							{
								"patchline": {
									"source": [
										"basic-3",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-9",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-11",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-12",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-13",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-14",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-16",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-5",
										0
									],
									"destination": [
										"basic-6",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-6",
										0
									],
									"destination": [
										"basic-17",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-8",
										0
									],
									"destination": [
										"basic-9",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-17",
										0
									],
									"destination": [
										"basic-18",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-17",
										0
									],
									"destination": [
										"basic-20",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"basic-20",
										0
									],
									"destination": [
										"basic-21",
										0
									]
								}
							}
						]
					},
					"saved_object_attributes": {
						"description": "",
						"digest": "",
						"globalpatchername": "",
						"tags": ""
					},
					"varname": "basic_tab",
					"id": "top-3"
				}
			},
			{
				"box": {
					"fontname": "Arial",
					"fontsize": 13.0,
					"maxclass": "newobj",
					"text": "p random",
					"patching_rect": [
						100.0,
						85.0,
						88.0,
						23.0
					],
					"numinlets": 0,
					"numoutlets": 0,
					"outlettype": [],
					"patcher": {
						"fileversion": 1,
						"appversion": {
							"major": 9,
							"minor": 1,
							"revision": 0,
							"architecture": "x64",
							"modernui": 1
						},
						"classnamespace": "box",
						"rect": [
							100.0,
							126.0,
							680.0,
							574.0
						],
						"bglocked": 0,
						"openinpresentation": 0,
						"default_fontsize": 13.0,
						"default_fontface": 0,
						"default_fontname": "Arial",
						"gridonopen": 1,
						"gridsize": [
							15.0,
							15.0
						],
						"gridsnaponopen": 1,
						"objectsnaponopen": 1,
						"statusbarvisible": 2,
						"toolbarvisible": 1,
						"lefttoolbarpinned": 0,
						"toptoolbarpinned": 0,
						"righttoolbarpinned": 0,
						"bottomtoolbarpinned": 0,
						"toolbars_unpinned_last_save": 0,
						"tallnewobj": 0,
						"boxanimatetime": 200,
						"enablehscroll": 1,
						"enablevscroll": 1,
						"devicewidth": 0.0,
						"description": "",
						"digest": "",
						"tags": "",
						"style": "",
						"subpatcher_template": "",
						"showontab": 1,
						"assistshowspatchername": 0,
						"boxes": [
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 24.0,
									"maxclass": "comment",
									"text": "Randomness",
									"patching_rect": [
										10.0,
										10.0,
										300.0,
										33.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "random-1"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "set random layers randomness on top of the waveform. intensity sets how strongly modes 2 and 3 pull each value toward a random one, and interval sets how many steps mode 3 takes to glide to each new random target.",
									"patching_rect": [
										10.0,
										48.0,
										650.0,
										40.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 2,
									"id": "random-2"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "mode",
									"patching_rect": [
										30.0,
										100.0,
										60.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "random-3"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "umenu",
									"items": [
										"no",
										"random",
										",",
										"replace",
										",",
										"multi",
										",",
										"multi",
										"interp"
									],
									"patching_rect": [
										30.0,
										125.0,
										120.0,
										23.0
									],
									"numinlets": 1,
									"numoutlets": 3,
									"outlettype": [
										"int",
										"",
										""
									],
									"parameter_enable": 0,
									"id": "random-4"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "prepend set random",
									"patching_rect": [
										30.0,
										160.0,
										122.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-5"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "0  no random: the waveform as it is\n1  replace: a new random value from 0.0 to 2.0 every step\n2  multi: move toward a new random value by intensity\n3  multi interp: like multi, but the random value glides to a new target every interval steps",
									"patching_rect": [
										215.0,
										100.0,
										445.0,
										80.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 5,
									"id": "random-6"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "intensity (default 0.05): 0 = none, 1 = fully random",
									"patching_rect": [
										30.0,
										200.0,
										360.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "random-7"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "set intensity 0.05",
									"patching_rect": [
										30.0,
										225.0,
										120.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-8"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "set intensity 0.3",
									"patching_rect": [
										160.0,
										225.0,
										114.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-9"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "set intensity 1",
									"patching_rect": [
										284.0,
										225.0,
										102.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-10"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "interval, for mode 3 (default 1)",
									"patching_rect": [
										30.0,
										260.0,
										260.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "random-11"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "set interval 1",
									"patching_rect": [
										30.0,
										285.0,
										96.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-12"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "set interval 10",
									"patching_rect": [
										136.0,
										285.0,
										104.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-13"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "waveform",
									"patching_rect": [
										420.0,
										260.0,
										80.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "random-14"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "wavetype 0",
									"patching_rect": [
										420.0,
										285.0,
										76.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-15"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "wavetype 5",
									"patching_rect": [
										506.0,
										285.0,
										76.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-16"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "sine / constant",
									"patching_rect": [
										420.0,
										310.0,
										120.0,
										21.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "random-17"
								}
							},
							{
								"box": {
									"maxclass": "button",
									"patching_rect": [
										30.0,
										325.0,
										24.0,
										24.0
									],
									"numinlets": 1,
									"numoutlets": 1,
									"outlettype": [
										"bang"
									],
									"parameter_enable": 0,
									"id": "random-18"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "draw 100 steps",
									"patching_rect": [
										58.0,
										324.0,
										110.0,
										25.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"bubble": 1,
									"id": "random-19"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "uzi 100",
									"patching_rect": [
										30.0,
										360.0,
										60.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 3,
									"outlettype": [
										"bang",
										"bang",
										"int"
									],
									"id": "random-20"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "breakgen",
									"patching_rect": [
										30.0,
										395.0,
										64.0,
										23.0
									],
									"numinlets": 1,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "random-21"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "zl.stream 100",
									"patching_rect": [
										30.0,
										430.0,
										92.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 2,
									"outlettype": [
										"",
										""
									],
									"id": "random-22"
								}
							},
							{
								"box": {
									"maxclass": "multislider",
									"patching_rect": [
										30.0,
										460.0,
										330.0,
										100.0
									],
									"numinlets": 1,
									"numoutlets": 2,
									"outlettype": [
										"",
										""
									],
									"parameter_enable": 0,
									"size": 100,
									"settype": 1,
									"setminmax": [
										0.0,
										2.0
									],
									"ignoreclick": 1,
									"id": "random-23"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "Try multi interp with intensity 0.3 and interval 10 on the constant waveform: the tempo wanders slowly around a steady pulse instead of following a regular wave.",
									"patching_rect": [
										385.0,
										400.0,
										275.0,
										80.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 4,
									"id": "random-24"
								}
							}
						],
						"lines": [
							{
								"patchline": {
									"source": [
										"random-5",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-8",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-9",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-10",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-12",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-13",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-15",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-16",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-4",
										0
									],
									"destination": [
										"random-5",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-18",
										0
									],
									"destination": [
										"random-20",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-20",
										0
									],
									"destination": [
										"random-21",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-21",
										0
									],
									"destination": [
										"random-22",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"random-22",
										0
									],
									"destination": [
										"random-23",
										0
									]
								}
							}
						]
					},
					"saved_object_attributes": {
						"description": "",
						"digest": "",
						"globalpatchername": "",
						"tags": ""
					},
					"id": "top-4"
				}
			},
			{
				"box": {
					"fontname": "Arial",
					"fontsize": 13.0,
					"maxclass": "newobj",
					"text": "p write",
					"patching_rect": [
						198.0,
						85.0,
						80.0,
						23.0
					],
					"numinlets": 0,
					"numoutlets": 0,
					"outlettype": [],
					"patcher": {
						"fileversion": 1,
						"appversion": {
							"major": 9,
							"minor": 1,
							"revision": 0,
							"architecture": "x64",
							"modernui": 1
						},
						"classnamespace": "box",
						"rect": [
							100.0,
							126.0,
							680.0,
							574.0
						],
						"bglocked": 0,
						"openinpresentation": 0,
						"default_fontsize": 13.0,
						"default_fontface": 0,
						"default_fontname": "Arial",
						"gridonopen": 1,
						"gridsize": [
							15.0,
							15.0
						],
						"gridsnaponopen": 1,
						"objectsnaponopen": 1,
						"statusbarvisible": 2,
						"toolbarvisible": 1,
						"lefttoolbarpinned": 0,
						"toptoolbarpinned": 0,
						"righttoolbarpinned": 0,
						"bottomtoolbarpinned": 0,
						"toolbars_unpinned_last_save": 0,
						"tallnewobj": 0,
						"boxanimatetime": 200,
						"enablehscroll": 1,
						"enablevscroll": 1,
						"devicewidth": 0.0,
						"description": "",
						"digest": "",
						"tags": "",
						"style": "",
						"subpatcher_template": "",
						"showontab": 1,
						"assistshowspatchername": 0,
						"boxes": [
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 24.0,
									"maxclass": "comment",
									"text": "Writing breakpoints",
									"patching_rect": [
										10.0,
										10.0,
										400.0,
										33.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"id": "write-1"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "writefile saves a run of values as a breakpoint file: plain text, one value per line. modmetro~ loads it with its open message and applies one value per beat. writebuf writes the values into a buffer~ instead.",
									"patching_rect": [
										10.0,
										48.0,
										650.0,
										40.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 2,
									"id": "write-2"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "writefile 200 0.2",
									"patching_rect": [
										30.0,
										105.0,
										118.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "write-3"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "200 beats that stay within 20% of the tempo (0.8 to 1.2). A Save dialog opens first.",
									"patching_rect": [
										240.0,
										100.0,
										420.0,
										40.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 2,
									"id": "write-4"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "writefile 200",
									"patching_rect": [
										30.0,
										155.0,
										96.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "write-5"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "Full depth: beats from zero length up to twice as long. The depth argument only applies when it is below 1.",
									"patching_rect": [
										240.0,
										150.0,
										420.0,
										40.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 2,
									"id": "write-6"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "sr 10000",
									"patching_rect": [
										30.0,
										205.0,
										66.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "write-7"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "The waveform keeps going between writes. Send sr to start the next file from the beginning of the cycle.",
									"patching_rect": [
										240.0,
										200.0,
										420.0,
										40.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 2,
									"id": "write-8"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "message",
									"text": "writebuf breakgen-help 1000",
									"patching_rect": [
										30.0,
										255.0,
										176.0,
										23.0
									],
									"numinlets": 2,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "write-9"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "Writes up to 1000 values into the buffer~, stopping at its end. These center on 0.0 instead of 1.0, the form modmetro~'s audiomod input expects. Every channel gets the same value.",
									"patching_rect": [
										240.0,
										250.0,
										420.0,
										58.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 3,
									"id": "write-10"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "breakgen",
									"patching_rect": [
										30.0,
										330.0,
										64.0,
										23.0
									],
									"numinlets": 1,
									"numoutlets": 1,
									"outlettype": [
										""
									],
									"id": "write-11"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "newobj",
									"text": "buffer~ breakgen-help 100",
									"patching_rect": [
										30.0,
										380.0,
										162.0,
										23.0
									],
									"numinlets": 1,
									"numoutlets": 2,
									"outlettype": [
										"float",
										"bang"
									],
									"id": "write-12"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "double-click to see what was written",
									"patching_rect": [
										198.0,
										379.0,
										240.0,
										25.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"bubble": 1,
									"id": "write-13"
								}
							},
							{
								"box": {
									"fontname": "Arial",
									"fontsize": 13.0,
									"maxclass": "comment",
									"text": "Each value written is the output scaled toward 1.0: (value - 1) x depth + 1, so a sine written with depth 0.2 starts like this:\n1.000000\n1.012558\n1.025067",
									"patching_rect": [
										30.0,
										430.0,
										630.0,
										95.0
									],
									"numinlets": 1,
									"numoutlets": 0,
									"linecount": 5,
									"id": "write-14"
								}
							}
						],
						"lines": [
							{
								"patchline": {
									"source": [
										"write-3",
										0
									],
									"destination": [
										"write-11",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"write-5",
										0
									],
									"destination": [
										"write-11",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"write-7",
										0
									],
									"destination": [
										"write-11",
										0
									]
								}
							},
							{
								"patchline": {
									"source": [
										"write-9",
										0
									],
									"destination": [
										"write-11",
										0
									]
								}
							}
						]
					},
					"saved_object_attributes": {
						"description": "",
						"digest": "",
						"globalpatchername": "",
						"tags": ""
					},
					"id": "top-5"
				}
			},
			{
				"box": {
					"fontname": "Arial",
					"fontsize": 13.0,
					"maxclass": "newobj",
					"text": "p ?",
					"patching_rect": [
						288.0,
						85.0,
						40.0,
						23.0
					],
					"numinlets": 0,
					"numoutlets": 0,
					"outlettype": [],
					"varname": "q_tab",
					"patcher": {
						"fileversion": 1,
						"appversion": {
							"major": 9,
							"minor": 1,
							"revision": 0,
							"architecture": "x64",
							"modernui": 1
						},
						"classnamespace": "box",
						"rect": [
							100.0,
							126.0,
							680.0,
							574.0
						],
						"bglocked": 0,
						"openinpresentation": 0,
						"default_fontsize": 13.0,
						"default_fontface": 0,
						"default_fontname": "Arial",
						"gridonopen": 1,
						"gridsize": [
							15.0,
							15.0
						],
						"gridsnaponopen": 1,
						"objectsnaponopen": 1,
						"statusbarvisible": 2,
						"toolbarvisible": 1,
						"lefttoolbarpinned": 0,
						"toptoolbarpinned": 0,
						"righttoolbarpinned": 0,
						"bottomtoolbarpinned": 0,
						"toolbars_unpinned_last_save": 0,
						"tallnewobj": 0,
						"boxanimatetime": 200,
						"enablehscroll": 1,
						"enablevscroll": 1,
						"devicewidth": 0.0,
						"description": "",
						"digest": "",
						"tags": "",
						"style": "",
						"subpatcher_template": "",
						"showontab": 1,
						"assistshowspatchername": 0,
						"boxes": [],
						"lines": []
					},
					"saved_object_attributes": {
						"description": "",
						"digest": "",
						"globalpatchername": "",
						"tags": ""
					},
					"id": "top-6"
				}
			}
		],
		"lines": [],
		"showrootpatcherontab": 0
	}
}