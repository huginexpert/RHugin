\name{triangulate.RHuginDomain}
\alias{triangulate}
\alias{triangulate.RHuginDomain}

\title{Triangulate}

\description{
Triangulate a domain.
}

\usage{
triangulate(object, ...)
\method{triangulate}{RHuginDomain}(object, method = "best.greedy", order, start, max.separators = 0, max.separator.size = 0, ...)
}

\arguments{
  \item{object}{an RHugin domain.}
  \item{method}{a character string specifying the triangulation method. The choices are \code{"clique.size"}, \code{"clique.weight"}, \code{"fill.in.size"}, \code{"fill.in.weight"}, \code{"best.greedy"} and \code{"total.weight"}. The default, \code{"best.greedy"}, is the method used by the \code{compile} function when compiling a domain that has not been triangulated in advance.}
  \item{order}{a character vector specifying the elimination sequence.  It must contain each continuous node and each discrete node in \code{object} exactly once and the continuous nodes must precede the discrete nodes.  When provided, \code{object} is triangulated using this elimination sequence; the method in \code{method} is not used.}
  \item{start}{a character vector specifying an initial triangulation for the \code{"total.weight"} method. Like \code{order}, it must contain each continuous node and each discrete node in \code{object} exactly once and the continuous nodes must precede the discrete nodes.}
  \item{max.separators}{a nonnegative integer value specifying the maximum number of minimal separators to generate when using the \code{"total.weight"} method.  The default value of \code{0} is interpreted as unlimited.}
  \item{max.separator.size}{a nonnegative integer value specifying the maximum size of minimal separators to keep when using the \code{"total.weight"} method.  The default value of \code{0} is interpreted as unlimited. This argument is ignored unless \code{start} is also provided.}
  \item{\dots}{additional arguments are ignored.}
}

\details{
The Triangulation section in the Compilation chapter in the HUGIN API Reference Manual describes the triangulations methods in detail.  
If the \code{order} argument is present then \code{object} is triangulated using the provided elimination sequence.  All other arguments are ignored.
}

\value{
a character vector containing the node names in the order used to triangulate \code{object} (that is, the elimination sequence).
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_domain_triangulate}, \code{h_domain_get_elimination_order}, \code{h_domain_triangulate_with_order}, \code{h_domain_set_initial_triangulation}, \code{h_domain_set_max_number_of_separators} and \code{h_domain_set_max_separator_size}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\note{
The \code{\link[RHugin]{compile}} function automatically triangulates an untriangulated domain using the default method ("best.greedy").  If the domain is already triangulated, then that triangulation is used.
}

\seealso{
\code{\link[RHugin]{compile}}.
}

\examples{
demo("asia", echo = FALSE)


# Triangulate the domain and store the elimination sequence
eo <- triangulate(asia, method = "clique.weight")


# Uncompile also utriangulates
uncompile(asia)


# Triangulate using the total.weight method with default settings
triangulate(asia, method = "total.weight")
uncompile(asia)


# Triangulate using the total.weight method with custom settings
triangulate(asia, method = "total.weight", start = eo, max.separators = 100000,
            max.separator.size = 500)
uncompile(asia)


# Triangulate using a known elimination sequence
triangulate(asia, order = eo)
uncompile(asia)
}

\keyword{programming}


