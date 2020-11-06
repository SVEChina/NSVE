{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/screen.vs",
    "fs" : "shader/code/filter/filterHaze.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[
                { "name" : "u_invert", "type" : "fvec2", "value" : "1.0,1.0" },
                { "name" : "dis", "type" : "f32", "value" : "0.0" },
                { "name" : "slope", "type" : "f32", "value" : "0.0" },
                { "name" : "hazeColor", "type" : "fvec3", "value" : "1.0,0.0,1.0" }
            ]
        }
    ]
}
