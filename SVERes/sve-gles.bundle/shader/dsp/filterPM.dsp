{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "nor",
    "vs" : "shader/code/screen.vs",
    "fs" : "shader/code/screen.fs",
    "sampler": [ { "name" : "aTexture0" ,"stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[
                { "name" : "shadows", "type" : "f32", "value" : "0.0" },
                { "name" : "highlights", "type" : "f32", "value" : "0.0" },
                { "name" : "contrast", "type" : "f32", "value" : "0.0" },
                { "name" : "saturation", "type" : "f32", "value" : "0.0" },
                { "name" : "brightness", "type" : "f32", "value" : "0.0" },
                { "name" : "whitening", "type" : "f32", "value" : "0.0" },
                { "name" : "gamma", "type" : "f32", "value" : "0.0" },
                { "name" : "redShift", "type" : "f32", "value" : "0.0" },
                { "name" : "greenShift", "type" : "f32", "value" : "0.0" },
                { "name" : "blueShift", "type" : "f32", "value" : "0.0" },
                { "name" : "sdredShift", "type" : "f32", "value" : "0.0" },
                { "name" : "sdgreenShift", "type" : "f32", "value" : "0.0" },
                { "name" : "sdblueShift", "type" : "f32", "value" : "0.0" },
                { "name" : "hhredShift", "type" : "f32", "value" : "0.0" },
                { "name" : "hhgreenShift", "type" : "f32", "value" : "0.0" },
                { "name" : "hhblueShift", "type" : "f32", "value" : "0.0" },
                { "name" : "temperature", "type" : "f32", "value" : "0.0" },
                { "name" : "tint", "type" : "f32", "value" : "0.0" }
            ]
        }
    ]
}
