//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

package wAPB.src.linklayer.ethernet.ARPPathSwitch;
import wAPB.src.linklayer.contract.ILearningTableWAPB;


//
// This module handles the mapping between ports and MAC addresses.
//
// Entries are deleted if their age exceeds a certain limit.
//
// If needed, address tables can be pre-loaded from text files at the beginning
// of the simulation; this controlled by the addressTableFile module parameter.
//
simple LearningTableNewWAPB like ILearningTableWAPB
{
    parameters:
        @class(wapb::LearningTableNewWAPB);       
        @display("i=block/table2");
        double agingTime @unit("s") = default(120s);
        //string addressTableFile = default("");
}
