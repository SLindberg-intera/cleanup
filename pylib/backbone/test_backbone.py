"""
    This module creates directories and files in the process
    of testing.  It should remove all of them but take care not
    to run this script in a directory that is under version 
    control so that the temporary files aren't added to the repository

"""

import unittest
import backbone
import os
import sys
import json
import itertools

try:
    sys.path.append("pylib\\fingerprint")
    import fingerprint
except Exception as e:
    raise e

"""********** TEST HELPERS *******************
This section 
    sets up a structure where there are two work products
    (one version each)

    work product 2 references work product 1
    work product 1 references nothing

    these files are created on disk along with fingerprints
    and a block chain

"""
START_DIR = os.path.join("ignore", "temp")

KEY = 'Work Product 1'
KEY2 = 'Work Product 2'
version = 'v1.2.3'
version2 = 'v0a'

keydir = os.path.join(START_DIR, KEY)
key2dir = os.path.join(START_DIR, KEY2)
versiondir = os.path.join(keydir, version)
version2dir = os.path.join(key2dir, version2)
datadir = os.path.join(versiondir, 'data')
data2dir = os.path.join(version2dir, 'data')
datafile = os.path.join(datadir, 'test_file.txt')
data2file = os.path.join(data2dir, 'test_file.txt')
metadir = os.path.join(versiondir, 'meta')
meta2dir = os.path.join(version2dir, 'meta')

FILE_CONTENTS = 'HELLO WORLD\n'
""" The above represents a dummy data file associated with a work product.

    don't change the above line; it will change the fingerprint
    that is referenced in the tests
"""


def create_data(filename):
    with open(filename, 'w') as f:
        f.write(FILE_CONTENTS)

def create_path(pathname):
    try:
        os.makedirs(pathname)
    except FileExistsError as e:
        if os.path.isdir(pathname):
            return
        raise e 

def remove_path(pathname):
    try:
        os.rmdir(pathname)
    except Exception as e:
        raise e

def make_blockfile(fingerprint, inheritance, outfile):
    d = {"Hash":fingerprint, "Inheritance":inheritance}
    with open(outfile, 'w') as f:
        f.write(json.dumps(d))

FINGERPRINT = backbone.FINGER_FILENAME 
INHERITANCE1 = []
INHERITANCE2 = [os.path.join("..","..", "..", KEY, version)]
BLOCK1 = os.path.join(metadir, backbone.ICF_BLOCK_FILENAME)
BLOCK2 = os.path.join(meta2dir, backbone.ICF_BLOCK_FILENAME)

def fingerprint_file(finger_file_in, finger_file_out):
    filename = FINGERPRINT
    s = fingerprint.extract_fingerprints(finger_file_in)
    outfile = os.path.join(finger_file_out, filename)
    fingerprint.to_file(outfile, s)

def create_test_data():
    create_path(START_DIR)
    create_path(datadir)
    create_path(data2dir)
    create_path(metadir)
    create_path(meta2dir)
    create_data(datafile)
    create_data(data2file)
    fingerprint_file(datadir, metadir)
    fingerprint_file(data2dir, meta2dir)
    fingerprint = backbone.get_fingerprint(
            os.path.join(metadir, FINGERPRINT))
    fingerprint2 = backbone.get_fingerprint(
            os.path.join(meta2dir, FINGERPRINT))
    
    make_blockfile(fingerprint, INHERITANCE1, BLOCK1)
    make_blockfile(fingerprint2, INHERITANCE2, BLOCK2)

def destroy_test_data():
    os.remove(datafile)
    os.remove(data2file)
    os.remove(os.path.join(metadir, FINGERPRINT))
    os.remove(os.path.join(meta2dir, FINGERPRINT))
    os.remove(BLOCK1)
    os.remove(BLOCK2)
    remove_path(datadir)
    remove_path(data2dir)
    remove_path(metadir)
    remove_path(meta2dir)
    remove_path(versiondir)
    remove_path(version2dir)
    remove_path(keydir)
    remove_path(key2dir)
    remove_path(START_DIR)


"""***********  Actual Tests **************"""

class TestWorkProductVersion(unittest.TestCase):
    def setUp(self):
        create_test_data()
        self.wp1 = backbone.WorkProductVersion(versiondir)
        self.wp2 = backbone.WorkProductVersion(version2dir)
    
    def tearDown(self):
        destroy_test_data()

    def test_setUp(self):
        self.assertTrue(os.path.isdir(metadir))
        self.assertTrue(os.path.isdir(datadir))

    def test_fingerprint(self):
        f = backbone.get_fingerprint(os.path.join(metadir, FINGERPRINT))
        self.assertTrue("56c2988" in f)

    def test_get_version(self):
        v1 = backbone.get_version(versiondir)
        v2 = backbone.get_version(version2dir)
        self.assertTrue(v1>v2)

    def test_version_number(self):
        v = backbone.get_version(versiondir)
        v2 = self.wp1.version_number
        self.assertEqual(v, v2)

    def test_version_str(self):
        v = self.wp1.version_str
        self.assertEqual(v, version)
        v2 = self.wp2.version_str
        self.assertEqual(v2, version2)

    def test_fingerprint(self):
        f1 = self.wp1.fingerprint
        f2 = self.wp2.fingerprint
        self.assertEqual(f1, f2)

    def test_block(self):
        """ can we get the related Block object and is it 
        connected correctly """
        block = self.wp1.block
        self.assertEqual(len(block.nodes), 1)
        self.assertEqual(len(block.connections), 0)
        block2 = self.wp2.block
        self.assertEqual(len(block2.nodes), 2)
        self.assertEqual(len(block2.connections), 1)
        
    def test_from_block(self):
        block = self.wp1.block
        wp3 = backbone.WorkProductVersion.from_block(block)
        self.assertEqual(wp3, self.wp1)
        self.assertNotEqual(wp3, self.wp2)

    def test_work_product_name(self):
        wp1 = self.wp1.work_product_name
        wp2 = self.wp2.work_product_name
        self.assertEqual(wp1, KEY)
        self.assertEqual(wp2, KEY2)

    def test_summary(self):
        summary = self.wp2.get_summary()
        self.assertTrue( KEY in summary)
        self.assertTrue( KEY2 in summary)
        self.assertTrue(self.wp2.path in summary)
        self.assertTrue(self.wp1.path in summary)

        summary = self.wp1.get_summary()
        self.assertTrue(self.wp1.path in summary)
        self.assertFalse(self.wp2.path in summary)

    def test_explain_version(self):
        e1 = backbone.WorkProductVersion.explain_version(versiondir)
        e2 = backbone.WorkProductVersion.explain_version(version2dir)
        self.assertTrue("Summary of" in e1)

    def test_get_children_paths(self):
        """
        wp1 should have 1 child (wp2)
        wp2 should have no children
        """
        self.assertTrue(len(self.wp2._get_children_paths())==0)
        self.assertTrue(len(self.wp1._get_children_paths())==1)
        self.assertTrue(
                self.wp1._get_children_paths()[0]==os.path.abspath(self.wp2.path)
        )

    def test_children(self):
        """ same as _get_children_paths except class instances """
        p = self.wp1.children
        self.assertTrue(p[0]==self.wp2)
        p2 = self.wp2.children
        self.assertTrue(p2==[])
    
    def test_parents(self):
        """
        wp1 should have no parents
        wp2 should have one parent (wp1)
        """
        p2 = self.wp2.parents
        p1 = self.wp1.parents
        self.assertTrue(len(p1)==0)
        self.assertTrue(len(p2)==1)
        self.assertTrue(p2[0]==self.wp1)

    def test_WorkProduct(self):
        wps = backbone.WorkProducts(self.wp1.all_work_products_path)
        versions = [wp.most_recent_version for wp in wps]
        self.assertTrue(v in [self.wp1, self.wp2] for v in versions)


if __name__=="__main__":
    unittest.main()
