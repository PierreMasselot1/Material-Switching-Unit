# This is just for personal experimentation at this time. If you happen to have a usecase for this script let me know and I will rewrite it to be more user friendly and add more features.
import os

FILE_NAME = "TipTest"
WRITE_DIRECTORY = "./FilamentTipTesting/filament_test_1"
CAMERA = False
EXTRUDER_POSITION_XYZ = (100, 100, 150)


def increment_file_version(filename):
    # check if a file of filename_* exists in the directory
    files_in_dir = os.listdir(WRITE_DIRECTORY)

    # Get largest current version number
    current_version = 0
    for file in files_in_dir:
        if filename in file:
            version = int(file.split("_")[-1].split(".")[0])
            if version > current_version:
                current_version = version

    if current_version > 0:
        return filename + "_" + str(current_version + 1) + ".gcode"

    # if no file of filename_* exists, return filename_1
    return filename + "_1" + ".gcode"


def filament_stamping(
    target_extract_temp,
    ramming_speed,
    stamping_speed,
    parking_position,
    extract_speed_start,
    extract_speed,
    ramming_distance,
    stamping_distance,
):
    gcode_commands = []
    # Allow cold extrusion for stamping
    gcode_commands.append("M302 P1")

    # COOLDOWN/EXTRUDER PRESSURE STABILIZATION
    gcode_commands.append("M104 S" + str(target_extract_temp))
    gcode_commands.append("M106 P0 S255")
    gcode_commands.append("M106 P1 S255")
    gcode_commands.append("G1 E-" + str(ramming_distance) + "F" + str(ramming_speed))

    # STAMPING
    gcode_commands.append("G1 E-" + str(stamping_distance) + "F" + str(stamping_speed))

    # EXTRACTION
    gcode_commands.append("G1 E-" + str(10) + "F" + str(extract_speed_start))
    move_distance = parking_position - 10
    gcode_commands.append("G1 E-" + str(move_distance) + "F" + str(extract_speed))

    # enable cold extrusion protection
    gcode_commands.append("M302 P0")
    return gcode_commands


def filament_change_and_picture_or_user_prompt(
    gcode_commands, picture_filename, settings
):
    # Append picture taking command when using octoprint
    if CAMERA:
        gcode_commands.append("M117 Picture time!")
        gcode_commands.append("G4 P1000")
        gcode_commands.append(
            "@OCTOLAPSE TAKE-SNAPSHOT"
        )  # might need to modify octoprint or create my own extension to allow for custom filenaming from gcode
        gcode_commands.append("M117 Picture taken!")
    else:
        gcode_commands.append("M117 " + str(settings))
        gcode_commands.append("M0")

    return gcode_commands


def setting_string_builder(
    target_extract_temp,
    ramming_speed,
    stamping_speed,
    parking_position,
    extract_speed_start,
    extract_speed,
    ramming_distance,
    stamping_distance,
):
    return (
        "Target extract temp: "
        + str(target_extract_temp)
        + ", Ramming speed: "
        + str(ramming_speed)
        + ", Stamping speed: "
        + str(stamping_speed)
        + ", Parking position: "
        + str(parking_position)
        + ", Extract speed start: "
        + str(extract_speed_start)
        + ", Extract speed: "
        + str(extract_speed)
        + ", Ramming distance: "
        + str(ramming_distance)
        + ", Stamping distance: "
        + str(stamping_distance)
    )


def filament_change(
    working_temp,
    ramming_speed,
    stamping_speed,
    parking_position,
    extract_speed_start,
    extract_speed,
    ramming_distance,
    stamping_distance,
    stream,
):
    gcode_commands = filament_stamping(
        working_temp,
        ramming_speed,
        stamping_speed,
        parking_position,
        extract_speed_start,
        extract_speed,
        ramming_distance,
        stamping_distance,
    )
    settings_string = setting_string_builder(
        working_temp,
        ramming_speed,
        stamping_speed,
        parking_position,
        extract_speed_start,
        extract_speed,
        ramming_distance,
        stamping_distance,
    )
    gcode_commands.insert(0, "; " + settings_string)
    all_commands = filament_change_and_picture_or_user_prompt(
        gcode_commands, "ramming_" + str(ramming_speed), settings_string
    )
    # Write the commands to the file
    for command in all_commands:
        stream.write(command + "\n")


def filament_tip_shaping_experimentation(filename_and_version, directory=None):
    # Create a new file in the directory
    stream = None
    if directory:
        stream = open(directory + "/" + filename_and_version, "w")
    else:
        stream = open(filename_and_version, "w")

    # TEST STAMPING WITHOUT COOLDOWN
    working_temp = 200
    parking_position = 50
    ramming_speed_range = (20, 40)
    stamping_speed_range = (20, 40)
    extract_speed_start_range = (20, 40)
    extract_speed_range = (
        1,
        40,
    )  # allow for cooldown? extract quickly to avoid stringing?
    ramming_distance_range = (1, 10)
    stamping_distance_range = (1, 4)

    num_tests = 10


    for i in range(num_tests):
        filament_change(
            working_temp,
            20,
            20,
            parking_position,
            20,
            20,
            1,
            1,
            stream,
        )

    return


filename_and_version = increment_file_version(FILE_NAME)
print("Opening input Gcode file and creating output file " + filename_and_version)

# if directory does not exist, create it
if not os.path.exists(WRITE_DIRECTORY):
    os.makedirs(WRITE_DIRECTORY)

filament_tip_shaping_experimentation(filename_and_version, WRITE_DIRECTORY)

end = input("Press enter to exit")
