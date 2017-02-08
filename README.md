---
documentclass: physycomen
title:  "json_undersampler"
author: "Fabbri, Sinigardi"
---

<a href="http://www.physycom.unibo.it"> 
<div class="image">
<img src="https://cdn.rawgit.com/physycom/templates/697b327d/logo_unibo.png" width="90" height="90" alt="© Physics of Complex Systems Laboratory - Physics and Astronomy Department - University of Bologna"> 
</div>
</a>
<a href="https://travis-ci.org/physycom/json_undersampler"> 
<div class="image">
<img src="https://travis-ci.org/physycom/json_undersampler.svg?branch=master" width="90" height="20" alt="Build Status"> 
</div>
</a>
<a href="https://ci.appveyor.com/project/cenit/json-undersampler"> 
<div class="image">
<img src="https://ci.appveyor.com/api/projects/status/cfjpqc7w8m9or1nu?svg=true" width="90" height="20" alt="Build Status"> 
</div>
</a>

### Purpose
This tool has been written to extract a subsample of an original set of data, undersampling it with a given ratio.


### Installation
**make** and a **C++11** compatible compiler are required. Clone the repo and type ``make`` in your favourite shell, it should be enough in most cases.
There's also a **VS2015** solution avalaible.   
Contains [jsoncons](https://github.com/danielaparker/jsoncons) as a git submodule.


### Usage
```
json_undersampler.exe -i input.json -o output.json -u undersampling
```
where `input.json` must be an existing and valid .json file, and with -u you should give and integer undersampling factor.

More details can be found in our technical description of the file formats (document still not published)

