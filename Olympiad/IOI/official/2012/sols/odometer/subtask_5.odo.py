# Solution for subtask 5 of Odometer.

# Author: Matteo Boscariol


print "jump 0_scan_all"

for i in xrange(0,15):

  print "%d_test_next_row:" % i
  print "right"
  print "border %d_scan_all" % (i+1)
  print "move"
  print "right"
  print "%d_test_next_row_l1:" % i
  print "border %d_test_next_row_l1end" % i
  print "move"
  print "jump %d_test_next_row_l1" % i
  print "%d_test_next_row_l1end:" % i
  print "right"

  print "%d_scan_all:" % i
  print "right"
  print "%d_test_scan_row:" % i
  for j in xrange(i):
    print "get"
  print "pebble %d_test_scan_row_continue" % i
  print "jump end_%d" % i
  print "%d_test_scan_row_continue:" % i
  for j in xrange(i):
    print "put"
  print "border %d_test_next_row" % i
  print "move"
  print "jump %d_test_scan_row" %i

for i in xrange(14,0,-1):
    print "end_%d:" % i
    print "put"
print "end_0:"
print "15_scan_all:"
