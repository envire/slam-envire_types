//
// Copyright (c) 2015, Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#pragma once

#include <octomap/AbstractOcTree.h>
#include <envire_core/serialization/BinaryBufferHelper.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>

namespace octomap
{
    typedef boost::shared_ptr< ::octomap::AbstractOcTree > AbstractOcTreePtr;
}

namespace boost { namespace serialization {

    template<class Archive>
    void load(Archive & ar, octomap::AbstractOcTreePtr & octree, const unsigned int version)
    {
        std::vector<uint8_t> buffer;
        ar >> buffer;
        if(!buffer.empty())
        {
            envire::core::BinaryInputBuffer buffer_helper(buffer);
            std::istream istream(&buffer_helper);
            octree.reset(::octomap::AbstractOcTree::read(istream));
        }
    }

    template<class Archive>
    void save(Archive & ar, const octomap::AbstractOcTreePtr & octree, const unsigned int version)
    {
        std::vector<uint8_t> buffer;
        buffer.reserve(octree->memoryUsage());
        envire::core::BinaryOutputBuffer buffer_helper(&buffer);
        std::ostream ostream(&buffer_helper);
         if(octree.get() != NULL)
            octree->write(ostream);
         ar << buffer;
    }

    template<class Archive>
    void serialize(Archive & ar, octomap::AbstractOcTreePtr & octree, const unsigned int version)
    {
        split_free(ar, octree, version);
    }

}}
