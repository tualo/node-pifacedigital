{
  "targets": [{
      "target_name": "pifacedigital",
      "include_dirs": [ '/usr/local/include', "<!(node -e \"require('nan')\")" ],
      "sources": [
        "src/c/init.cc",
        "src/c/NPIFaceDigital.cc"
      ],
      "link_settings":{
        "libraries": [
            "-lpifacedigital",
            "-lmcp23s17"
        ]
      }
 }]
}
