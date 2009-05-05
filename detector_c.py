#!/usr/bin/python

import datetime, re, sys, time
import lightblue
import MySQLdb

def main():
  # 20s offset for C
  time.sleep(20)

  h = 'randomfoo.net'
  conn = MySQLdb.connect(user='blueball', passwd='blueball', db='blueball', host=h)
  c = conn.cursor()

  devlist = lightblue.finddevices()
  # devlist = [('00:16:CB:0B:E8:0F', u'spentstick-lm', 3154188), ('00:0F:DE:F0:EA:B9', None, 5374468), ('00:17:D5:EC:1A:BD', u'Lonza', 5374468), ('00:1B:63:DA:A7:70', None, 3146252)]
  scantime = int(time.time())

  for dev in devlist:
    # store
    mac = dev[0]
    name = dev[1]
    if not name:
      name = "Unnamed"
    type = dev[2]

    # print dev
    (service, major, minor) = class_of_device(type)

    # Log
    sql = "INSERT INTO history (id, name, type, scantime, sensor) VALUES (%s, %s, %s, %s, 'c')"
    c.execute(sql, (mac, name, type, scantime)) 

    # Device
    sql = "INSERT INTO devices (id, name, service, major, minor, lastseen, c_seen) VALUES (%s, %s, %s, %s, %s, %s, %s) ON DUPLICATE KEY UPDATE name = VALUES(name), service = VALUES(service), major = VALUES(major), minor = VALUES(minor), lastseen = VALUES(lastseen), c_seen = VALUES(c_seen)"

    c.execute(sql, (mac, name, service, major, minor, scantime, scantime))

    # Increment count
    sql = "SELECT COUNT(*) FROM history WHERE id = %s"
    c.execute(sql, (mac,))
    row = c.fetchone()
    total_count = row[0]
    sql = "UPDATE devices SET total_count = %s WHERE id = %s"
    c.execute(sql, (total_count, mac))

    conn.commit()

    # print

def class_of_device(type):
  t = ['', '', '']

  # Masks
  SERVICE_MASK = 0xffe000
  MAJOR_MASK   = 0x001f00
  MINOR_MASK   = 0x0000fc

  # Services
  services = {}
  services['LIMITED_DISCOVERY_SERVICE'] = 0x002000
  services['RESERVED1_SERVICE'] = 0x004000
  services['RESERVED2_SERVICE'] = 0x008000
  services['POSITIONING_SERVICE'] = 0x010000
  services['NETWORKING_SERVICE'] = 0x020000
  services['RENDERING_SERVICE'] = 0x040000
  services['CAPTURING_SERVICE'] = 0x080000
  services['OBJECT_TRANSFER_SERVICE'] = 0x100000
  services['AUDIO_SERVICE'] = 0x200000
  services['TELEPHONY_SERVICE'] = 0x400000
  services['INFORMATION_SERVICE'] = 0x800000

  # Major Device Classes
  major_devices = {}
  major_devices['MAJOR_MISCELLANEOUS'] = 0x0000
  major_devices['MAJOR_COMPUTER'] = 0x0100
  major_devices['MAJOR_PHONE'] = 0x0200
  major_devices['MAJOR_LAN_ACCESS'] = 0x0300
  major_devices['MAJOR_AUDIO'] = 0x0400
  major_devices['MAJOR_PERIPHERAL'] = 0x0500
  major_devices['MAJOR_IMAGING'] = 0x0600
  major_devices['MAJOR_UNCLASSIFIED'] = 0x1F00

  # Minor Device Classes
  minor_devices = {}
  minor_devices['COMPUTER_MINOR_UNCLASSIFIED'] = 0x00
  minor_devices['COMPUTER_MINOR_DESKTOP'] = 0x04
  minor_devices['COMPUTER_MINOR_SERVER'] = 0x08
  minor_devices['COMPUTER_MINOR_LAPTOP'] = 0x0c
  minor_devices['COMPUTER_MINOR_HANDHELD'] = 0x10
  minor_devices['COMPUTER_MINOR_PALM'] = 0x14
  minor_devices['COMPUTER_MINOR_WEARABLE'] = 0x18
  minor_devices['PHONE_MINOR_UNCLASSIFIED'] = 0x00
  minor_devices['PHONE_MINOR_CELLULAR'] = 0x04
  minor_devices['PHONE_MINOR_CORDLESS'] = 0x08
  minor_devices['PHONE_MINOR_SMARTPHONE'] = 0x0c
  minor_devices['PHONE_MINOR_WIRED_MODEM'] = 0x10
  minor_devices['PHONE_MINOR_ISDN'] = 0x14
  minor_devices['PHONE_MINOR_BANANA'] = 0x18
  minor_devices['LAN_MINOR_TYPE_MASK'] = 0x1c
  minor_devices['LAN_MINOR_ACCESS_MASK'] = 0xe0
  minor_devices['LAN_MINOR_UNCLASSIFIED'] = 0x00
  minor_devices['LAN_MINOR_ACCESS_0_USED'] = 0x00
  minor_devices['LAN_MINOR_ACCESS_17_USED'] = 0x20
  minor_devices['LAN_MINOR_ACCESS_33_USED'] = 0x40
  minor_devices['LAN_MINOR_ACCESS_50_USED'] = 0x60
  minor_devices['LAN_MINOR_ACCESS_67_USED'] = 0x80
  minor_devices['LAN_MINOR_ACCESS_83_USED'] = 0xa0
  minor_devices['LAN_MINOR_ACCESS_99_USED'] = 0xc0
  minor_devices['LAN_MINOR_ACCESS_FULL'] = 0xe0
  minor_devices['AUDIO_MINOR_UNCLASSIFIED'] = 0x00
  minor_devices['AUDIO_MINOR_HEADSET'] = 0x04
  minor_devices['AUDIO_MINOR_HANDS_FREE'] = 0x08
  # minor_devices['AUDIO_MINOR_RESERVED'] = 0x0c
  minor_devices['AUDIO_MINOR_MICROPHONE'] = 0x10
  minor_devices['AUDIO_MINOR_LOUDSPEAKER'] = 0x14
  minor_devices['AUDIO_MINOR_HEADPHONES'] = 0x18
  minor_devices['AUDIO_MINOR_PORTABLE_AUDIO'] = 0x1c
  minor_devices['AUDIO_MINOR_CAR_AUDIO'] = 0x20
  minor_devices['AUDIO_MINOR_SET_TOP_BOX'] = 0x24
  minor_devices['AUDIO_MINOR_HIFI_AUDIO'] = 0x28
  minor_devices['AUDIO_MINOR_VCR'] = 0x2c
  minor_devices['AUDIO_MINOR_VIDEO_CAMERA'] = 0x30
  minor_devices['AUDIO_MINOR_CAMCORDER'] = 0x34
  minor_devices['AUDIO_MINOR_VIDEO_MONITOR'] = 0x38
  minor_devices['AUDIO_MINOR_VIDEO_DISPLAY_LOUDSPEAKER'] = 0x3c
  minor_devices['AUDIO_MINOR_VIDEO_DISPLAY_CONFERENCING'] = 0x40
  # minor_devices['AUDIO_MINOR_RESERVED'] = 0x44
  minor_devices['AUDIO_MINOR_GAMING_TOY'] = 0x48
  minor_devices['PERIPHERAL_MINOR_TYPE_MASK'] = 0x3c
  minor_devices['PERIPHERAL_MINOR_KEYBOARD_MASK'] = 0x40
  minor_devices['PERIPHERAL_MINOR_POINTER_MASK'] = 0x80
  minor_devices['PERIPHERAL_MINOR_UNCLASSIFIED'] = 0x00
  minor_devices['PERIPHERAL_MINOR_JOYSTICK'] = 0x04
  minor_devices['PERIPHERAL_MINOR_GAMEPAD'] = 0x08
  minor_devices['PERIPHERAL_MINOR_REMOTE_CONTROL'] = 0x0c
  minor_devices['PERIPHERAL_MINOR_SENSING'] = 0x10
  minor_devices['PERIPHERAL_MINOR_DIGITIZER'] = 0x14
  minor_devices['PERIPHERAL_MINOR_CARD_READER'] = 0x18
  minor_devices['IMAGING_MINOR_DISPLAY_MASK'] = 0x10
  minor_devices['IMAGING_MINOR_CAMERA_MASK'] = 0x20
  minor_devices['IMAGING_MINOR_SCANNER_MASK'] = 0x40
  minor_devices['IMAGING_MINOR_PRINTER_MASK'] = 0x80

  # Service Type
  # TODO: Find out what the SERVICE_MASK should be...
  ''' 
  service = type & SERVICE_MASK 
  print hex(SERVICE_MASK)
  print hex(type)
  for st, si in services.items():
    print service, st, si
    if si == service:
      print st
  '''

  # Major Device Type
  major = type & MAJOR_MASK 
  for mt, mi in major_devices.items():
    if mi == major:
      t[1] = mt[6:]
      break

  # Minor Device Type
  minor = type & MINOR_MASK 
  for mt, mi in minor_devices.items():
    if mi == minor and re.search(t[1], mt):
      offset = len(t[1]) + 7
      t[2] = mt[offset:]
      break

  return t

if __name__ == '__main__':
  main()

# >>> devs[0].getNameOrAddress()
# u'gmwils 6600'
# >>> devs[0].isConnected()


# bt = [('00:17:D5:EC:1A:BD', u'Lonza', 5374468)]
