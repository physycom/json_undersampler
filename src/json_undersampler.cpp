/* Copyright 2015 - Alessandro Fabbri, Stefano Sinigardi */

/***************************************************************************
This file is part of json_distance.

json_distance is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

json_distance is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with json_distance. If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>

#include "jsoncons/json.hpp"

#define GEODESIC_DEG_TO_M         111070.4                              // conversion [deg] -> [meter]
#define RAD_TO_DEG                57.2957795131                         // 180/pi
#define DEG_TO_RAD                1.745329251e-2                        // pi/180
#define EPSILON                   1e-5

#define MAJOR_VERSION             1
#define MINOR_VERSION             0

void usage(char* progname) {
  // Usage
  std::cout << std::endl << "\tUsage:\t" << progname << " -i [input.json] -o [output.json] -u [undersampling]" << std::endl << std::endl;

  exit(1);
}

int main(int argc, char** argv) {
  std::cout << "JsonUndersampler v" << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;

  std::string input_name, output_name;
  int undersampling;
  bool all = false;

  if (argc > 6) { /* Parse arguments, if there are arguments supplied */
    for (int i = 1; i < argc; i++) {
      if ((argv[i][0] == '-') || (argv[i][0] == '/')) {       // switches or options...
        switch (tolower(argv[i][1])) {
        case 'i':
          input_name = argv[++i];
          break;
        case 'o':
          output_name = argv[++i];
          break;
        case 'u':
          undersampling = atoi(argv[++i]);
          break;
        default:    // no match...
          std::cout << "ERROR: Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
          usage(argv[0]);
        }
      }
      else {
        std::cout << "ERROR: Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
        usage(argv[0]);
      }
    }
  }
  else {
    std::cout << "ERROR: No flags specified. Read usage and relaunch properly." << std::endl;
    usage(argv[0]);
  }

  // Safety checks
  std::ifstream input_file(input_name);
  if (!input_file) {
    std::cout << "FAILED: Input file " << input_name << " could not be opened. Quitting..." << std::endl;
    exit(2);
  }

  std::ofstream output_file(output_name);
  if (!output_file) {
    std::cout << "FAILED: Output file " << output_name << " could not be opened. Quitting..." << std::endl;
    exit(22);
  }

  if (undersampling == 0) {
    std::cout << "WARNING: Undersampling factor is 0, set it to 1" << std::endl;
    undersampling = 1;
  }

  // Parsing JSON and dumping to file
  jsoncons::json input_json = jsoncons::json::parse_file(input_name);
  jsoncons::json output_json;

  if (input_json.is_array()) {
    output_json = jsoncons::json(jsoncons::json::an_array);
    for (size_t i = 0; i < input_json.size(); i++) {
      if (i % undersampling) continue;
      output_json.add(input_json[i]);
    }
  }
  else if (input_json.is_object()) {
    int i = 0;
    for (auto it = input_json.begin_members(); it != input_json.end_members(); it++, i++) {
      if (i % undersampling) continue;
      output_json[it->name()] = it->value();
    }
  }

  output_file << jsoncons::pretty_print(output_json) << std::endl;
  output_file.close();
  
  return 0;
}