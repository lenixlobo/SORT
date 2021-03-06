/*
    This file is a part of SORT(Simple Open Ray Tracing), an open-source cross
    platform physically based renderer.
 
    Copyright (c) 2011-2019 by Cao Jiayin - All rights reserved.
 
    SORT is a free software written for educational purpose. Anyone can distribute
    or modify it under the the terms of the GNU General Public License Version 3 as
    published by the Free Software Foundation. However, there is NO warranty that
    all components are functional in a perfect manner. Without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    General Public License for more details.
 
    You should have received a copy of the GNU General Public License along with
    this program. If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
 */

#include "mesh.h"
#include "entity/visual.h"
#include "stream/stream.h"
#include "managers/matmanager.h"
#include "entity/entity.h"
#include "stream/stream.h"

void BufferMemory::ApplyTransform( const Transform& transform ){
    for (MeshVertex& mv : m_vertices) {
        mv.m_position = transform(mv.m_position);
        mv.m_normal = (transform.invMatrix.Transpose())(mv.m_normal).Normalize();
    }
}

void BufferMemory::GenSmoothTagent(){
	// generate tangent for each triangle
    std::vector<std::vector<Vector>> tangent(m_vertices.size());
    for (auto mi : m_indices) {
        const auto t = genTagentForTri(mi);

        tangent[mi.m_id[0]].push_back(t);
        tangent[mi.m_id[1]].push_back(t);
        tangent[mi.m_id[2]].push_back(t);
    }
    for (auto i = 0u; i < m_vertices.size(); ++i) {
        Vector t;
        for (auto v : tangent[i])
            t += v;
        m_vertices[i].m_tangent = t.Normalize();
    }
}

void BufferMemory::GenUV(){
    if (m_hasUV || m_vertices.empty())
        return;

    Point center;
    for( const MeshVertex& mv : m_vertices )
        center = center + mv.m_position;
    center /= (float)m_vertices.size();

    for (MeshVertex& mv : m_vertices) {
        Vector diff = mv.m_position - center;
        diff.Normalize();
        mv.m_texCoord.x = SphericalTheta(diff) * INV_PI;
        mv.m_texCoord.y = SphericalPhi(diff) * INV_TWOPI;
    }
}

Vector BufferMemory::genTagentForTri( const MeshFaceIndex& mi ) const{
    const auto& _v0 = m_vertices[mi.m_id[0]];
    const auto& _v1 = m_vertices[mi.m_id[1]];
    const auto& _v2 = m_vertices[mi.m_id[2]];

	// get three vertexes
	const auto& p0 = _v0.m_position ;
	const auto& p1 = _v1.m_position ;
	const auto& p2 = _v2.m_position ;

	const auto u0 = _v0.m_texCoord.x;
	const auto u1 = _v1.m_texCoord.x;
	const auto u2 = _v2.m_texCoord.x;
	const auto v0 = _v0.m_texCoord.y;
	const auto v1 = _v1.m_texCoord.y;
	const auto v2 = _v2.m_texCoord.y;

	const auto du1 = u0 - u2;
	const auto du2 = u1 - u2;
	const auto dv1 = v0 - v2;
	const auto dv2 = v1 - v2;
	const auto dp1 = p0 - p2;
	const auto dp2 = p1 - p2;

	const auto determinant = du1 * dv2 - dv1 * du2 ;
	if( determinant == 0.0f ){
		const auto n = Normalize( Cross( p0 - p1 , p0 - p2 ) );
		Vector t0 , t1;
		CoordinateSystem( n , t0 , t1 );
		return t0;
	}
	return ( dv2 * dp1 - dv1 * dp2 ) / determinant;
}

// serialization interface for BufferMemory
void BufferMemory::Serialize( IStreamBase& stream ){
    stream >> m_hasUV;
    unsigned int vb_cnt, ib_cnt;
    stream >> vb_cnt;
    m_vertices.resize(vb_cnt);
    for (MeshVertex& mv : m_vertices)
        stream >> mv.m_position >> mv.m_normal >> mv.m_texCoord;

    stream >> ib_cnt;
    m_indices.resize(ib_cnt);
    for (auto& mi : m_indices) {
        stream >> mi.m_id[0] >> mi.m_id[1] >> mi.m_id[2];
        int mat_id = -1;
        stream >> mat_id;
        mi.m_mat = MatManager::GetSingleton().GetMaterial(mat_id);
    }
}