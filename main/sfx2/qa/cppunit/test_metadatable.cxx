/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#include <sal/cppunit.h>
#include <rtl/ustrbuf.hxx>

#include <com/sun/star/util/DateTime.hpp>
#include <com/sun/star/util/Date.hpp>
#include <com/sun/star/util/Duration.hpp>

#include <sfx2/Metadatable.hxx>
#include <sfx2/XmlIdRegistry.hxx>


using namespace ::com::sun::star;


namespace {

class MetadatableTest
    : public ::CppUnit::TestFixture
{
public:
    virtual void setUp();
    virtual void tearDown();

    void test();

    CPPUNIT_TEST_SUITE(MetadatableTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

private:
};

void MetadatableTest::setUp()
{
}

void MetadatableTest::tearDown()
{
}


class MockMetadatable
    : public ::sfx2::Metadatable
{
private:
    ::sfx2::IXmlIdRegistry & m_rRegistry;

public:
    MockMetadatable(::sfx2::IXmlIdRegistry & i_rReg,
            bool const i_isInClip = false)
        : m_rRegistry(i_rReg)
        , m_bInClipboard(i_isInClip), m_bInUndo(false), m_bInContent(true) {}
    bool m_bInClipboard;
    bool m_bInUndo;
    bool m_bInContent;
    virtual bool IsInClipboard() const { return m_bInClipboard; }
    virtual bool IsInUndo() const { return m_bInUndo; }
    virtual bool IsInContent() const { return m_bInContent; }
    virtual ::sfx2::IXmlIdRegistry& GetRegistry() { return m_rRegistry; }
    virtual ::com::sun::star::uno::Reference<
        ::com::sun::star::rdf::XMetadatable > MakeUnoObject() { return 0; }
};

static bool operator==(beans::StringPair p1, beans::StringPair p2)
{
    return p1.First == p2.First && p1.Second == p2.Second;
}

void MetadatableTest::test()
{
    OSL_TRACE("SwMetadatable test(): start\n");
    ::std::auto_ptr< ::sfx2::IXmlIdRegistry > const pReg(
        ::sfx2::createXmlIdRegistry(false) );
    ::std::auto_ptr< ::sfx2::IXmlIdRegistry > const pRegClip(
        ::sfx2::createXmlIdRegistry(true) );

    MockMetadatable m1(*pReg);
    MockMetadatable m2(*pReg);
    MockMetadatable m3(*pReg);
    MockMetadatable m4(*pReg);
    MockMetadatable m5(*pReg);
    ::rtl::OUString empty;
    ::rtl::OUString content( ::rtl::OUString::createFromAscii("content.xml") );
    ::rtl::OUString styles ( ::rtl::OUString::createFromAscii("styles.xml") );
    ::rtl::OUString sid1( ::rtl::OUString::createFromAscii("id1") );
    ::rtl::OUString sid2( ::rtl::OUString::createFromAscii("id2") );
    ::rtl::OUString sid3( ::rtl::OUString::createFromAscii("id3") );
    ::rtl::OUString sid4( ::rtl::OUString::createFromAscii("id4") );
    beans::StringPair id1(content, sid1);
    beans::StringPair id2(content, sid2);
    beans::StringPair id3(content, sid3);
    beans::StringPair id4(styles,  sid4);
    beans::StringPair id3e(empty,  sid3);
    beans::StringPair id4e(empty,  sid4);
    m1.SetMetadataReference(id1);
    CPPUNIT_ASSERT_MESSAGE("set failed", m1.GetMetadataReference() == id1);
    try {
        m2.SetMetadataReference(id1);
        CPPUNIT_ASSERT_MESSAGE("set duplicate succeeded", false);
    } catch (lang::IllegalArgumentException) { }
    m1.SetMetadataReference(id1);
    CPPUNIT_ASSERT_MESSAGE("set failed (existing)",
            m1.GetMetadataReference() == id1);
    m1.EnsureMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("ensure failed (existing)",
            m1.GetMetadataReference() == id1);

    m2.EnsureMetadataReference();
    beans::StringPair m2id(m2.GetMetadataReference());
    CPPUNIT_ASSERT_MESSAGE("ensure failed", m2id.Second.getLength());
    m2.EnsureMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("ensure failed (idempotent)",
            m2.GetMetadataReference() == m2id);

    m1.m_bInUndo = true;
    CPPUNIT_ASSERT_MESSAGE("move to undo failed",
            !m1.GetMetadataReference().Second.getLength());

    m1.m_bInUndo = false;
    CPPUNIT_ASSERT_MESSAGE("move from undo failed",
            m1.GetMetadataReference() == id1);

    m1.m_bInUndo = true;
    try {
        m2.SetMetadataReference(id1); // steal!
    } catch (lang::IllegalArgumentException &) {
        CPPUNIT_FAIL("set duplicate to undo failed");
    }
    m1.m_bInUndo = false;
    CPPUNIT_ASSERT_MESSAGE("move from undo: duplicate",
            !m1.GetMetadataReference().Second.getLength());

    m3.RegisterAsCopyOf(m2);
    CPPUNIT_ASSERT_MESSAGE("copy: source", m2.GetMetadataReference() == id1);
    CPPUNIT_ASSERT_MESSAGE("copy: duplicate",
            !m3.GetMetadataReference().Second.getLength());
    m4.RegisterAsCopyOf(m3);
    CPPUNIT_ASSERT_MESSAGE("copy: source", m2.GetMetadataReference() == id1);
    CPPUNIT_ASSERT_MESSAGE("copy: duplicate",
            !m3.GetMetadataReference().Second.getLength());
    CPPUNIT_ASSERT_MESSAGE("copy: duplicate",
            !m4.GetMetadataReference().Second.getLength());
    m2.m_bInUndo = true;
    CPPUNIT_ASSERT_MESSAGE("duplicate to undo",
            m3.GetMetadataReference() == id1);
    CPPUNIT_ASSERT_MESSAGE("duplicate to undo",
            !m2.GetMetadataReference().Second.getLength());
    m2.m_bInUndo = false;
    CPPUNIT_ASSERT_MESSAGE("duplicate from undo",
            m2.GetMetadataReference() == id1);
    CPPUNIT_ASSERT_MESSAGE("duplicate from undo",
            !m3.GetMetadataReference().Second.getLength());

    m4.EnsureMetadataReference(); // new!
    beans::StringPair m4id(m4.GetMetadataReference());
    CPPUNIT_ASSERT_MESSAGE("ensure on duplicate",
            m4id.Second.getLength() && !(m4id == id1));

    MockMetadatable mc1(*pRegClip, true); // in clipboard
    MockMetadatable mc2(*pRegClip, true);
    MockMetadatable mc3(*pRegClip, true);
    MockMetadatable mc4(*pRegClip, true);
    MockMetadatable m2p(*pReg);
    MockMetadatable m3p(*pReg);

    mc1.SetMetadataReference(id2);
    CPPUNIT_ASSERT_MESSAGE("set failed", mc1.GetMetadataReference() == id2);
    try {
        mc2.SetMetadataReference(id2);
        CPPUNIT_FAIL("set duplicate succeeded");
    } catch (lang::IllegalArgumentException) { }
    mc1.SetMetadataReference(id2);
    CPPUNIT_ASSERT_MESSAGE("set failed (existing)",
            mc1.GetMetadataReference() == id2);
    mc1.EnsureMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("ensure failed (existing)",
            mc1.GetMetadataReference() == id2);
    mc2.EnsureMetadataReference();
    beans::StringPair mc2id(mc2.GetMetadataReference());
    CPPUNIT_ASSERT_MESSAGE("ensure failed", mc2id.Second.getLength());
    mc2.EnsureMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("ensure failed (idempotent)",
            mc2.GetMetadataReference() == mc2id);
    mc2.RemoveMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("remove failed",
            !mc2.GetMetadataReference().Second.getLength());

    // set up mc2 as copy of m2 and mc3 as copy of m3
    mc3.RegisterAsCopyOf(m3);
    CPPUNIT_ASSERT_MESSAGE("copy to clipboard (latent)",
            !mc3.GetMetadataReference().Second.getLength() );
    mc2.RegisterAsCopyOf(m2);
    CPPUNIT_ASSERT_MESSAGE("copy to clipboard (non-latent)",
            mc2.GetMetadataReference() == id1);
    // paste mc2 to m2p and mc3 to m3p
    m2p.RegisterAsCopyOf(mc2);
    CPPUNIT_ASSERT_MESSAGE("paste from clipboard (non-latent)",
            !m2p.GetMetadataReference().Second.getLength() );
    m3p.RegisterAsCopyOf(mc3);
    CPPUNIT_ASSERT_MESSAGE("paste from clipboard (latent)",
            !m3p.GetMetadataReference().Second.getLength() );
    // delete m2, m2p, m3
    m2.RemoveMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("remove failed",
            !m2.GetMetadataReference().Second.getLength());
    CPPUNIT_ASSERT_MESSAGE("paste-remove (non-latent)",
            m2p.GetMetadataReference() == id1);
    m2p.RemoveMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("remove failed",
            !m2p.GetMetadataReference().Second.getLength());
    CPPUNIT_ASSERT_MESSAGE("paste-remove2 (non-latent)",
            m3.GetMetadataReference() == id1);
    m3.RemoveMetadataReference();
    CPPUNIT_ASSERT_MESSAGE("remove failed",
            !m3.GetMetadataReference().Second.getLength());
    CPPUNIT_ASSERT_MESSAGE("paste-remove (latent)",
            m3p.GetMetadataReference() == id1);
    // delete mc2
    mc2.SetMetadataReference(beans::StringPair());
    CPPUNIT_ASSERT_MESSAGE("in clipboard becomes non-latent",
            !mc3.GetMetadataReference().Second.getLength() );
    // paste mc2
    m2p.RegisterAsCopyOf(mc2);
    CPPUNIT_ASSERT_MESSAGE("remove-paste",
            !m2p.GetMetadataReference().Second.getLength());
    CPPUNIT_ASSERT_MESSAGE("remove-paste (stolen)",
            m3p.GetMetadataReference() == id1);

    // auto-detect stream
    m5.SetMetadataReference(id3e);
    CPPUNIT_ASSERT_MESSAGE("auto-detect (content)",
            m5.GetMetadataReference() == id3);
    m5.m_bInContent = false;
    m5.SetMetadataReference(id4e);
    CPPUNIT_ASSERT_MESSAGE("auto-detect (styles)",
            m5.GetMetadataReference() == id4);

    OSL_TRACE("sfx2::Metadatable test(): finished\n");
}


CPPUNIT_TEST_SUITE_REGISTRATION(MetadatableTest);

}

CPPUNIT_PLUGIN_IMPLEMENT();

