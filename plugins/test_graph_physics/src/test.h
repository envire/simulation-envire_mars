/*
 *  Copyright 2013, DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * \file test.h
 * \author Arne Böckmann
 * \brief Plugin
 */

#pragma once
// set define if you want to extend the gui
//#define PLUGIN_WITH_MARS_GUI

#include <mars/interfaces/sim/MarsPluginTemplate.h>
#include <mars/interfaces/MARSDefs.h>
#include <mars/cfg_manager/CFGManagerInterface.h>
#include <string>
#include <vector>
#include <envire_core/items/Frame.hpp>
#include <mars/interfaces/NodeData.h>
#include <mars/interfaces/JointData.h>


namespace envire {namespace core {
  class TransformGraph;
}}

/**A plugin used for testing the TransformGraph in mars
 * */

namespace mars {
  namespace plugins {
    namespace test_graph_physics {

      /**
       * A very simple plugin that tries to convert all ConfigMaps found in the
       * transform graph into NodeData and draw it.
       * */
      class TestGraph2 : public mars::interfaces::MarsPluginTemplate
      {

      public:
        TestGraph2(lib_manager::LibManager *theManager);
        ~TestGraph2();

        // LibInterface methods
        int getLibVersion() const
        { return 1; }
        const std::string getLibName() const
        { return std::string("TestGraph2"); }
        CREATE_MODULE_INFO();

        // MarsPlugin methods
        void init();
        void reset();
        void update(mars::interfaces::sReal time_ms);
        
        void dropItem();

        void jointedItems();

        mars::interfaces::NodeData randomNodeData(envire::core::FrameId id);
    
        // CFGClient methods
        virtual void cfgUpdateProperty(cfg_manager::cfgPropertyStruct _property);
      private:
        envire::core::FrameId getNextFrameId();
        
        /**returns the uuid of the item that has been addded */
        boost::uuids::uuid addNodeToFrame(envire::core::FrameId id, mars::interfaces::NodeData data);
        /**Adds a joint between frames @p id and @p id2 to the frame @p jointId */
        void addJointToFrame(envire::core::FrameId id, mars::interfaces::JointData& data,
                             boost::uuids::uuid itemId1, boost::uuids::uuid itemId2);


      private:
        boost::random::mt19937 rng; 
        envire::core::FrameId floor;
        int itemId;

      }; // end of class definition TestTreeMars

    } // end of namespace TestTreeMars
  } // end of namespace plugins
} // end of namespace mars
